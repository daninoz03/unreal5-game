// VerdantHeartCharacter.cpp

#include "Characters/VerdantHeartCharacter.h"
#include "Components/HealthComponent.h"
#include "Components/CombatComponent.h"
#include "VerdantHeart.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TimerManager.h"

AVerdantHeartCharacter::AVerdantHeartCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Configure capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 350.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 50.0f, 80.0f);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = true;
	CameraBoom->ProbeChannel = ECC_Camera;

	// Create follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->FieldOfView = 75.0f;

	// Create health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	// Create combat component
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

	// Initialize stamina
	CurrentStamina = MaxStamina;
}

void AVerdantHeartCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set up input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}

	// Initialize stamina
	CurrentStamina = MaxStamina;

	// Bind to death event
	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddDynamic(this, &AVerdantHeartCharacter::OnDeath);
	}

	UE_LOG(LogVerdantHeart, Log, TEXT("VerdantHeartCharacter initialized"));
}

void AVerdantHeartCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateStamina(DeltaTime);
	UpdateMovementState();
}

void AVerdantHeartCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up Enhanced Input bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Movement
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVerdantHeartCharacter::Move);
		}

		// Looking
		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVerdantHeartCharacter::Look);
		}

		// Jumping
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AVerdantHeartCharacter::StartJump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AVerdantHeartCharacter::StopJump);
		}

		// Sprinting
		if (SprintAction)
		{
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AVerdantHeartCharacter::StartSprint);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AVerdantHeartCharacter::StopSprint);
		}

		// Dodging
		if (DodgeAction)
		{
			EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this, &AVerdantHeartCharacter::StartDodge);
		}

		// Light Attack
		if (LightAttackAction)
		{
			EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Started, this, &AVerdantHeartCharacter::LightAttack);
		}

		// Heavy Attack
		if (HeavyAttackAction)
		{
			EnhancedInputComponent->BindAction(HeavyAttackAction, ETriggerEvent::Started, this, &AVerdantHeartCharacter::StartHeavyAttack);
			EnhancedInputComponent->BindAction(HeavyAttackAction, ETriggerEvent::Completed, this, &AVerdantHeartCharacter::ReleaseHeavyAttack);
		}

		// Interact
		if (InteractAction)
		{
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AVerdantHeartCharacter::Interact);
		}

		// Focus Mode
		if (FocusAction)
		{
			EnhancedInputComponent->BindAction(FocusAction, ETriggerEvent::Started, this, &AVerdantHeartCharacter::StartFocusMode);
			EnhancedInputComponent->BindAction(FocusAction, ETriggerEvent::Completed, this, &AVerdantHeartCharacter::StopFocusMode);
		}
	}
}

void AVerdantHeartCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	LastMoveInput = FVector(MovementVector.X, MovementVector.Y, 0.0f);

	if (Controller != nullptr && !bIsDodging)
	{
		// Get control rotation (camera direction)
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward and right vectors
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement input
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AVerdantHeartCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AVerdantHeartCharacter::StartJump(const FInputActionValue& Value)
{
	if (!bIsDodging)
	{
		Jump();
	}
}

void AVerdantHeartCharacter::StopJump(const FInputActionValue& Value)
{
	StopJumping();
}

void AVerdantHeartCharacter::StartSprint(const FInputActionValue& Value)
{
	if (CurrentStamina > 0.0f && !bIsDodging)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		UE_LOG(LogVerdantHeart, Verbose, TEXT("Sprint started"));
	}
}

void AVerdantHeartCharacter::StopSprint(const FInputActionValue& Value)
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	UE_LOG(LogVerdantHeart, Verbose, TEXT("Sprint stopped"));
}

void AVerdantHeartCharacter::StartDodge(const FInputActionValue& Value)
{
	// Can't dodge if already dodging, in air, or no stamina
	if (bIsDodging || GetCharacterMovement()->IsFalling() || !ConsumeStamina(DodgeStaminaCost))
	{
		return;
	}

	PerformDodge();
}

void AVerdantHeartCharacter::PerformDodge()
{
	bIsDodging = true;
	SetMovementState(EMovementState::Dodging);

	// Determine dodge direction
	FVector DodgeDirection;
	if (LastMoveInput.SizeSquared() > 0.1f)
	{
		// Dodge in input direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		DodgeDirection = (ForwardDirection * LastMoveInput.Y + RightDirection * LastMoveInput.X).GetSafeNormal();
	}
	else
	{
		// Dodge backward
		DodgeDirection = -GetActorForwardVector();
	}

	// Apply dodge impulse
	LaunchCharacter(DodgeDirection * DodgeForce, true, false);

	// Set invulnerable
	if (HealthComponent)
	{
		HealthComponent->SetInvulnerable(true);

		// End invulnerability after duration
		GetWorldTimerManager().SetTimer(
			InvulnerabilityTimerHandle,
			[this]() { 
				if (HealthComponent) 
				{ 
					HealthComponent->SetInvulnerable(false); 
				} 
			},
			DodgeInvulnerabilityDuration,
			false
		);
	}

	// Play dodge montage if set
	if (DodgeMontage)
	{
		PlayAnimMontage(DodgeMontage);
	}

	// End dodge after duration
	GetWorldTimerManager().SetTimer(DodgeTimerHandle, this, &AVerdantHeartCharacter::EndDodge, DodgeDuration, false);

	UE_LOG(LogVerdantHeart, Log, TEXT("Dodge performed in direction: %s"), *DodgeDirection.ToString());
}

void AVerdantHeartCharacter::EndDodge()
{
	bIsDodging = false;
	UE_LOG(LogVerdantHeart, Log, TEXT("Dodge ended"));
}

void AVerdantHeartCharacter::LightAttack(const FInputActionValue& Value)
{
	if (CombatComponent && !bIsDodging)
	{
		CombatComponent->RequestLightAttack();
	}
}

void AVerdantHeartCharacter::StartHeavyAttack(const FInputActionValue& Value)
{
	if (CombatComponent && !bIsDodging)
	{
		CombatComponent->RequestHeavyAttack();
	}
}

void AVerdantHeartCharacter::ReleaseHeavyAttack(const FInputActionValue& Value)
{
	if (CombatComponent)
	{
		CombatComponent->ReleaseHeavyAttack();
	}
}

void AVerdantHeartCharacter::Interact(const FInputActionValue& Value)
{
	// Perform interaction trace
	FVector Start = FollowCamera->GetComponentLocation();
	FVector End = Start + FollowCamera->GetForwardVector() * 300.0f;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Interactable, QueryParams))
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			// Call interact on the hit actor - implement via interface in Blueprint
			UE_LOG(LogVerdantHeart, Log, TEXT("Interaction hit: %s"), *HitActor->GetName());
			// Interact interface will be implemented in Blueprint
		}
	}
}

void AVerdantHeartCharacter::StartFocusMode(const FInputActionValue& Value)
{
	bFocusModeActive = true;
	UE_LOG(LogVerdantHeart, Log, TEXT("Focus mode activated"));
	// Visual effect implementation in Blueprint
}

void AVerdantHeartCharacter::StopFocusMode(const FInputActionValue& Value)
{
	bFocusModeActive = false;
	UE_LOG(LogVerdantHeart, Log, TEXT("Focus mode deactivated"));
}

void AVerdantHeartCharacter::SetMovementState(EMovementState NewState)
{
	if (CurrentMovementState != NewState)
	{
		EMovementState OldState = CurrentMovementState;
		CurrentMovementState = NewState;
		OnMovementStateChanged.Broadcast(NewState, OldState);
	}
}

void AVerdantHeartCharacter::UpdateMovementState()
{
	// Don't update if dodging (handled separately)
	if (bIsDodging)
	{
		return;
	}

	// Determine state based on movement
	if (GetCharacterMovement()->IsFalling())
	{
		SetMovementState(GetVelocity().Z > 0 ? EMovementState::Jumping : EMovementState::Falling);
	}
	else if (GetVelocity().Size2D() < 10.0f)
	{
		SetMovementState(EMovementState::Idle);
	}
	else if (bIsSprinting)
	{
		SetMovementState(EMovementState::Sprinting);
	}
	else if (GetVelocity().Size2D() > WalkSpeed)
	{
		SetMovementState(EMovementState::Running);
	}
	else
	{
		SetMovementState(EMovementState::Walking);
	}
}

void AVerdantHeartCharacter::UpdateStamina(float DeltaTime)
{
	// Drain stamina while sprinting and moving
	if (bIsSprinting && GetVelocity().Size2D() > 10.0f)
	{
		CurrentStamina -= StaminaDrainRate * DeltaTime;
		CurrentStamina = FMath::Max(0.0f, CurrentStamina);
		TimeSinceStaminaUse = 0.0f;

		// Stop sprinting if out of stamina
		if (CurrentStamina <= 0.0f)
		{
			StopSprint(FInputActionValue());
		}
	}
	else
	{
		// Regenerate stamina after delay
		TimeSinceStaminaUse += DeltaTime;

		if (TimeSinceStaminaUse >= StaminaRegenDelay)
		{
			CurrentStamina += StaminaRegenRate * DeltaTime;
			CurrentStamina = FMath::Min(CurrentStamina, MaxStamina);
		}
	}
}

bool AVerdantHeartCharacter::ConsumeStamina(float Amount)
{
	if (CurrentStamina >= Amount)
	{
		CurrentStamina -= Amount;
		TimeSinceStaminaUse = 0.0f;
		return true;
	}
	return false;
}

void AVerdantHeartCharacter::RestoreStamina(float Amount)
{
	CurrentStamina = FMath::Min(CurrentStamina + Amount, MaxStamina);
}

void AVerdantHeartCharacter::OnDeath(UHealthComponent* OwningHealthComp)
{
	UE_LOG(LogVerdantHeart, Log, TEXT("Player died!"));

	// Disable input
	DisableInput(Cast<APlayerController>(Controller));

	// Play death animation / ragdoll - implement in Blueprint
	// Notify game mode - implement in Blueprint
}

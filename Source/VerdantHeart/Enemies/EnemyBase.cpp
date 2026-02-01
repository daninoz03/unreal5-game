// EnemyBase.cpp

#include "Enemies/EnemyBase.h"
#include "Components/HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "VerdantHeart.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	// Create health bar widget
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);
	HealthBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidget->SetDrawSize(FVector2D(100.0f, 10.0f));

	// Configure AI movement
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);

	// Set AI controller class - will be set in Blueprint
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	// Store home location
	HomeLocation = GetActorLocation();

	// Bind to death event
	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddDynamic(this, &AEnemyBase::OnDeath);
	}

	UE_LOG(LogVerdantHeart, Log, TEXT("Enemy %s spawned at %s"), *GetName(), *HomeLocation.ToString());
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update health bar visibility based on distance to player
	if (HealthBarWidget)
	{
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
		{
			if (APawn* PlayerPawn = PC->GetPawn())
			{
				float Distance = FVector::Dist(GetActorLocation(), PlayerPawn->GetActorLocation());
				HealthBarWidget->SetVisibility(Distance < 1500.0f && !bIsDead);
			}
		}
	}
}

void AEnemyBase::SetEnemyState(EEnemyState NewState)
{
	if (CurrentState != NewState && !bIsDead)
	{
		EEnemyState OldState = CurrentState;
		CurrentState = NewState;
		OnEnemyStateChanged.Broadcast(NewState, OldState);

		UE_LOG(LogVerdantHeart, Log, TEXT("Enemy %s state changed: %d -> %d"), 
			*GetName(), (int32)OldState, (int32)NewState);
	}
}

void AEnemyBase::SetTargetActor(AActor* NewTarget)
{
	TargetActor = NewTarget;
	if (NewTarget)
	{
		SetEnemyState(EEnemyState::Chasing);
		UE_LOG(LogVerdantHeart, Log, TEXT("Enemy %s targeting %s"), *GetName(), *NewTarget->GetName());
	}
}

void AEnemyBase::ClearTarget()
{
	TargetActor = nullptr;
	SetEnemyState(EEnemyState::Patrolling);
}

bool AEnemyBase::IsInAttackRange() const
{
	return TargetActor && GetDistanceToTarget() <= AttackRange;
}

float AEnemyBase::GetDistanceToTarget() const
{
	if (!TargetActor)
	{
		return MAX_FLT;
	}
	return FVector::Dist(GetActorLocation(), TargetActor->GetActorLocation());
}

void AEnemyBase::PerformAttack_Implementation()
{
	if (!TargetActor || bIsDead)
	{
		return;
	}

	// Check cooldown
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastAttackTime < AttackCooldown)
	{
		return;
	}

	LastAttackTime = CurrentTime;
	SetEnemyState(EEnemyState::Attacking);

	// Play attack animation
	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}

	// Apply damage (timing should be handled by anim notify in real implementation)
	UGameplayStatics::ApplyDamage(
		TargetActor,
		AttackDamage,
		GetController(),
		this,
		nullptr
	);

	UE_LOG(LogVerdantHeart, Log, TEXT("Enemy %s attacked %s for %.1f damage"), 
		*GetName(), *TargetActor->GetName(), AttackDamage);
}

void AEnemyBase::OnDamageReceived_Implementation(float Damage, AActor* DamageCauser)
{
	// Set the damage causer as target if we don't have one
	if (!TargetActor && DamageCauser)
	{
		// Try to get the pawn that caused the damage
		if (APawn* CauserPawn = Cast<APawn>(DamageCauser))
		{
			SetTargetActor(CauserPawn);
		}
		else if (AController* CauserController = DamageCauser->GetInstigatorController())
		{
			if (APawn* ControllerPawn = CauserController->GetPawn())
			{
				SetTargetActor(ControllerPawn);
			}
		}
	}

	UE_LOG(LogVerdantHeart, Log, TEXT("Enemy %s took %.1f damage from %s"), 
		*GetName(), Damage, DamageCauser ? *DamageCauser->GetName() : TEXT("Unknown"));
}

void AEnemyBase::OnDeath(UHealthComponent* OwningHealthComp)
{
	if (bIsDead)
	{
		return;
	}

	bIsDead = true;
	SetEnemyState(EEnemyState::Dead);

	HandleDeath();

	OnEnemyDeath.Broadcast(this);

	UE_LOG(LogVerdantHeart, Log, TEXT("Enemy %s died"), *GetName());
}

void AEnemyBase::HandleDeath_Implementation()
{
	// Disable collision
	SetActorEnableCollision(false);

	// Stop movement
	GetCharacterMovement()->StopMovementImmediately();

	// Hide health bar
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}

	// Destroy after delay (allows for death animation)
	SetLifeSpan(5.0f);
}

// VerdantHeartCharacter.h - Base player character class

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "VerdantHeartCharacter.generated.h"

// Forward declarations
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UHealthComponent;
class UCombatComponent;

// Movement state enum
UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Idle,
	Walking,
	Running,
	Sprinting,
	Jumping,
	Falling,
	Climbing,
	Dodging,
	Attacking
};

// Delegate for state changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMovementStateChanged, EMovementState, NewState, EMovementState, OldState);

UCLASS(config=Game)
class VERDANTHEART_API AVerdantHeartCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AVerdantHeartCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Getters for components
	UFUNCTION(BlueprintCallable, Category = "Character")
	UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	UCombatComponent* GetCombatComponent() const { return CombatComponent; }

	// State getters
	UFUNCTION(BlueprintCallable, Category = "Character|State")
	EMovementState GetMovementState() const { return CurrentMovementState; }

	UFUNCTION(BlueprintCallable, Category = "Character|State")
	bool IsSprinting() const { return bIsSprinting; }

	UFUNCTION(BlueprintCallable, Category = "Character|State")
	bool IsDodging() const { return bIsDodging; }

	UFUNCTION(BlueprintCallable, Category = "Character|State")
	bool IsFocusModeActive() const { return bFocusModeActive; }

	// Stamina getters
	UFUNCTION(BlueprintCallable, Category = "Character|Stamina")
	float GetCurrentStamina() const { return CurrentStamina; }

	UFUNCTION(BlueprintCallable, Category = "Character|Stamina")
	float GetMaxStamina() const { return MaxStamina; }

	UFUNCTION(BlueprintCallable, Category = "Character|Stamina")
	float GetStaminaPercent() const { return CurrentStamina / MaxStamina; }

	// Stamina management
	UFUNCTION(BlueprintCallable, Category = "Character|Stamina")
	bool ConsumeStamina(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Character|Stamina")
	void RestoreStamina(float Amount);

	// State change event
	UPROPERTY(BlueprintAssignable, Category = "Character")
	FOnMovementStateChanged OnMovementStateChanged;

protected:
	virtual void BeginPlay() override;

	// Input handlers
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);
	void StartSprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	void StartDodge(const FInputActionValue& Value);
	void LightAttack(const FInputActionValue& Value);
	void StartHeavyAttack(const FInputActionValue& Value);
	void ReleaseHeavyAttack(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void StartFocusMode(const FInputActionValue& Value);
	void StopFocusMode(const FInputActionValue& Value);

	// State management
	void SetMovementState(EMovementState NewState);
	void UpdateMovementState();

	// Stamina
	void UpdateStamina(float DeltaTime);

	// Dodge implementation
	void PerformDodge();
	void EndDodge();

	// Death handler
	UFUNCTION()
	void OnDeath(UHealthComponent* OwningHealthComp);

	// ---- COMPONENTS ----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCombatComponent* CombatComponent;

	// ---- INPUT ----

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* DodgeAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LightAttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* HeavyAttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* FocusAction;

	// ---- MOVEMENT SETTINGS ----

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float RunSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed = 850.0f;

	// ---- STAMINA SETTINGS ----

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina")
	float MaxStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina")
	float StaminaDrainRate = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina")
	float StaminaRegenRate = 15.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina")
	float StaminaRegenDelay = 1.0f;

	// ---- DODGE SETTINGS ----

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
	float DodgeForce = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
	float DodgeStaminaCost = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
	float DodgeDuration = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
	float DodgeInvulnerabilityDuration = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
	UAnimMontage* DodgeMontage;

	// ---- STATE ----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	EMovementState CurrentMovementState = EMovementState::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float CurrentStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float TimeSinceStaminaUse = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsSprinting = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsDodging = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bFocusModeActive = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	FVector LastMoveInput;

	// Timer handle for dodge
	FTimerHandle DodgeTimerHandle;
	FTimerHandle InvulnerabilityTimerHandle;
};

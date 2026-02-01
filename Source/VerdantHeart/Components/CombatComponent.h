// CombatComponent.h - Handles attacks, combos, and damage dealing

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

// Attack types
UENUM(BlueprintType)
enum class EAttackType : uint8
{
	None,
	LightAttack1,
	LightAttack2,
	LightAttack3,
	HeavyAttack,
	ChargedHeavyAttack,
	DodgeAttack
};

// Struct to hold attack data
USTRUCT(BlueprintType)
struct FAttackData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAttackType AttackType = EAttackType::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage = 15.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StaminaCost = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Range = 150.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackRadius = 30.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAnimMontage* AttackMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ComboWindowStart = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ComboWindowEnd = 0.6f;
};

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackStarted, EAttackType, AttackType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackEnded, EAttackType, AttackType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageDealt, AActor*, Target, float, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboReset);

UCLASS(ClassGroup=(VerdantHeart), meta=(BlueprintSpawnableComponent))
class VERDANTHEART_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Input handlers - call these from character
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RequestLightAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RequestHeavyAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ReleaseHeavyAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RequestDodgeAttack();

	// State queries
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool IsAttacking() const { return bIsAttacking; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool CanAttack() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 GetComboCount() const { return ComboCount; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool IsInComboWindow() const { return bInComboWindow; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool IsChargingHeavy() const { return bChargingHeavy; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	float GetChargePercent() const;

	// Called by animation notifies to handle hit detection
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EnableHitDetection();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void DisableHitDetection();

	// Called when attack montage ends
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void OnAttackMontageEnded();

	// Called when combo window opens
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void OpenComboWindow();

	// Called when combo window closes
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void CloseComboWindow();

	// Events
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnAttackStarted OnAttackStarted;

	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnAttackEnded OnAttackEnded;

	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnDamageDealt OnDamageDealt;

	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnComboReset OnComboReset;

protected:
	virtual void BeginPlay() override;

	// Execute the attack
	void ExecuteAttack(const FAttackData& AttackData);

	// Perform hit detection
	void PerformHitDetection();

	// Apply damage to a target
	void ApplyDamageToTarget(AActor* Target, float Damage);

	// Reset combo state
	void ResetCombo();

	// Attack data configuration - set these in Blueprint child class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Attacks")
	FAttackData LightAttack1Data;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Attacks")
	FAttackData LightAttack2Data;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Attacks")
	FAttackData LightAttack3Data;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Attacks")
	FAttackData HeavyAttackData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Attacks")
	FAttackData ChargedHeavyAttackData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Attacks")
	FAttackData DodgeAttackData;

	// Charge settings
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Charge")
	float ChargeTimeForFullCharge = 0.5f;

	// State
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat|State")
	bool bIsAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat|State")
	bool bInComboWindow = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat|State")
	bool bComboQueued = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat|State")
	int32 ComboCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat|State")
	bool bChargingHeavy = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat|State")
	float CurrentChargeTime = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat|State")
	bool bHitDetectionEnabled = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat|State")
	EAttackType CurrentAttackType = EAttackType::None;

	// Track what we've hit this swing to prevent double-hits
	UPROPERTY()
	TArray<AActor*> HitActorsThisSwing;

	// Reference to owner's mesh for attack traces
	UPROPERTY()
	class USkeletalMeshComponent* OwnerMesh;

	// Socket name for weapon trace
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName WeaponSocketName = "weapon_socket";

	// Current attack data being used
	FAttackData CurrentAttackData;
};

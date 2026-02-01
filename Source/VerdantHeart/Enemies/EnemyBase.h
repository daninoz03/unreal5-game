// EnemyBase.h - Base class for all enemies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

// Forward declarations
class UHealthComponent;
class UBehaviorTree;
class UWidgetComponent;

// Enemy state enum
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Patrolling,
	Alerted,
	Chasing,
	Attacking,
	Staggered,
	Dead
};

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnemyStateChanged, EEnemyState, NewState, EEnemyState, OldState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDeath, AEnemyBase*, Enemy);

UCLASS(Abstract)
class VERDANTHEART_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

	virtual void Tick(float DeltaTime) override;

	// Get components
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	// State management
	UFUNCTION(BlueprintCallable, Category = "Enemy|State")
	EEnemyState GetEnemyState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "Enemy|State")
	void SetEnemyState(EEnemyState NewState);

	// Target management
	UFUNCTION(BlueprintCallable, Category = "Enemy|Target")
	AActor* GetTargetActor() const { return TargetActor; }

	UFUNCTION(BlueprintCallable, Category = "Enemy|Target")
	void SetTargetActor(AActor* NewTarget);

	UFUNCTION(BlueprintCallable, Category = "Enemy|Target")
	void ClearTarget();

	UFUNCTION(BlueprintCallable, Category = "Enemy|Target")
	bool HasTarget() const { return TargetActor != nullptr; }

	// Combat
	UFUNCTION(BlueprintCallable, Category = "Enemy|Combat")
	bool IsInAttackRange() const;

	UFUNCTION(BlueprintCallable, Category = "Enemy|Combat")
	float GetDistanceToTarget() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy|Combat")
	void PerformAttack();

	// Called when this enemy takes damage - for reactions
	UFUNCTION(BlueprintNativeEvent, Category = "Enemy")
	void OnDamageReceived(float Damage, AActor* DamageCauser);

	// Events
	UPROPERTY(BlueprintAssignable, Category = "Enemy")
	FOnEnemyStateChanged OnEnemyStateChanged;

	UPROPERTY(BlueprintAssignable, Category = "Enemy")
	FOnEnemyDeath OnEnemyDeath;

	// Get behavior tree for AI controller
	UFUNCTION(BlueprintCallable, Category = "Enemy|AI")
	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

protected:
	virtual void BeginPlay() override;

	// Death handler
	UFUNCTION()
	void OnDeath(UHealthComponent* OwningHealthComp);

	// Handle death - override in child classes
	UFUNCTION(BlueprintNativeEvent, Category = "Enemy")
	void HandleDeath();

	// ---- COMPONENTS ----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* HealthBarWidget;

	// ---- AI SETTINGS ----

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	float DetectionRange = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	float LoseTargetRange = 1500.0f;

	// ---- COMBAT SETTINGS ----

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float AttackRange = 150.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float AttackDamage = 15.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float AttackCooldown = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	UAnimMontage* AttackMontage;

	// ---- PATROL SETTINGS ----

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	TArray<FVector> PatrolPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Patrol")
	float PatrolWaitTime = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patrol")
	int32 CurrentPatrolIndex = 0;

	// ---- STATE ----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	EEnemyState CurrentState = EEnemyState::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	AActor* TargetActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	FVector HomeLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float LastAttackTime = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsDead = false;
};

// HealthComponent.h - Reusable health system for player and enemies

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// Delegate for health change events - Blueprint can bind to these
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, UHealthComponent*, HealthComp, float, Health, float, HealthDelta, const class UDamageType*, DamageType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, UHealthComponent*, HealthComp);

UCLASS(ClassGroup=(VerdantHeart), meta=(BlueprintSpawnableComponent))
class VERDANTHEART_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	// Get current health
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth() const { return CurrentHealth; }

	// Get max health
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }

	// Get health as percentage (0-1)
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const { return CurrentHealth / MaxHealth; }

	// Check if dead
	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return bIsDead; }

	// Heal the owner
	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float HealAmount);

	// Set max health (also heals to new max if current > new max)
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetMaxHealth(float NewMaxHealth);

	// Increase max health by amount (for upgrades)
	UFUNCTION(BlueprintCallable, Category = "Health")
	void IncreaseMaxHealth(float Amount);

	// Set invulnerability (for dodge i-frames, etc.)
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetInvulnerable(bool bNewInvulnerable) { bIsInvulnerable = bNewInvulnerable; }

	// Check invulnerability
	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsInvulnerable() const { return bIsInvulnerable; }

	// Events that Blueprints can bind to
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeath OnDeath;

protected:
	virtual void BeginPlay() override;

	// Handle incoming damage
	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, 
		class AController* InstigatedBy, AActor* DamageCauser);

	// Current health value
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	bool bIsDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	bool bIsInvulnerable = false;
};

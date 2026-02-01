// HealthComponent.cpp

#include "Components/HealthComponent.h"
#include "VerdantHeart.h"
#include "GameFramework/Actor.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize health
	CurrentHealth = MaxHealth;

	// Bind to owner's damage event
	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);
	}
}

void UHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	// Ignore if already dead or invulnerable
	if (bIsDead || bIsInvulnerable || Damage <= 0.0f)
	{
		return;
	}

	// Apply damage
	float OldHealth = CurrentHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);
	float ActualDamage = OldHealth - CurrentHealth;

	UE_LOG(LogVerdantHeart, Log, TEXT("%s took %.1f damage. Health: %.1f/%.1f"), 
		*GetOwner()->GetName(), ActualDamage, CurrentHealth, MaxHealth);

	// Broadcast health change
	OnHealthChanged.Broadcast(this, CurrentHealth, -ActualDamage, DamageType);

	// Check for death
	if (CurrentHealth <= 0.0f)
	{
		bIsDead = true;
		OnDeath.Broadcast(this);
		
		UE_LOG(LogVerdantHeart, Log, TEXT("%s has died."), *GetOwner()->GetName());
	}
}

void UHealthComponent::Heal(float HealAmount)
{
	if (bIsDead || HealAmount <= 0.0f)
	{
		return;
	}

	float OldHealth = CurrentHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
	float ActualHeal = CurrentHealth - OldHealth;

	if (ActualHeal > 0.0f)
	{
		UE_LOG(LogVerdantHeart, Log, TEXT("%s healed for %.1f. Health: %.1f/%.1f"),
			*GetOwner()->GetName(), ActualHeal, CurrentHealth, MaxHealth);

		OnHealthChanged.Broadcast(this, CurrentHealth, ActualHeal, nullptr);
	}
}

void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = FMath::Max(1.0f, NewMaxHealth);
	CurrentHealth = FMath::Min(CurrentHealth, MaxHealth);
}

void UHealthComponent::IncreaseMaxHealth(float Amount)
{
	if (Amount > 0.0f)
	{
		MaxHealth += Amount;
		CurrentHealth += Amount; // Also heal by the increase amount
		
		UE_LOG(LogVerdantHeart, Log, TEXT("%s max health increased by %.1f. New max: %.1f"),
			*GetOwner()->GetName(), Amount, MaxHealth);
	}
}

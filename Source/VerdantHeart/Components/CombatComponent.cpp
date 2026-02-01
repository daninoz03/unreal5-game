// CombatComponent.cpp

#include "Components/CombatComponent.h"
#include "VerdantHeart.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Set default attack values
	LightAttack1Data.AttackType = EAttackType::LightAttack1;
	LightAttack1Data.Damage = 15.0f;
	LightAttack1Data.StaminaCost = 10.0f;
	LightAttack1Data.Range = 150.0f;
	LightAttack1Data.AttackRadius = 30.0f;

	LightAttack2Data.AttackType = EAttackType::LightAttack2;
	LightAttack2Data.Damage = 15.0f;
	LightAttack2Data.StaminaCost = 10.0f;
	LightAttack2Data.Range = 150.0f;
	LightAttack2Data.AttackRadius = 30.0f;

	LightAttack3Data.AttackType = EAttackType::LightAttack3;
	LightAttack3Data.Damage = 20.0f;
	LightAttack3Data.StaminaCost = 10.0f;
	LightAttack3Data.Range = 180.0f;
	LightAttack3Data.AttackRadius = 40.0f;

	HeavyAttackData.AttackType = EAttackType::HeavyAttack;
	HeavyAttackData.Damage = 35.0f;
	HeavyAttackData.StaminaCost = 25.0f;
	HeavyAttackData.Range = 180.0f;
	HeavyAttackData.AttackRadius = 50.0f;

	ChargedHeavyAttackData.AttackType = EAttackType::ChargedHeavyAttack;
	ChargedHeavyAttackData.Damage = 50.0f;
	ChargedHeavyAttackData.StaminaCost = 40.0f;
	ChargedHeavyAttackData.Range = 200.0f;
	ChargedHeavyAttackData.AttackRadius = 70.0f;

	DodgeAttackData.AttackType = EAttackType::DodgeAttack;
	DodgeAttackData.Damage = 20.0f;
	DodgeAttackData.StaminaCost = 15.0f;
	DodgeAttackData.Range = 150.0f;
	DodgeAttackData.AttackRadius = 30.0f;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to owner's mesh
	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		OwnerMesh = Character->GetMesh();
	}
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Update charge time if charging heavy attack
	if (bChargingHeavy)
	{
		CurrentChargeTime += DeltaTime;
	}

	// Perform hit detection if enabled
	if (bHitDetectionEnabled)
	{
		PerformHitDetection();
	}
}

bool UCombatComponent::CanAttack() const
{
	// Can attack if not currently attacking, or if in combo window
	return !bIsAttacking || bInComboWindow;
}

float UCombatComponent::GetChargePercent() const
{
	if (ChargeTimeForFullCharge <= 0.0f)
	{
		return 1.0f;
	}
	return FMath::Clamp(CurrentChargeTime / ChargeTimeForFullCharge, 0.0f, 1.0f);
}

void UCombatComponent::RequestLightAttack()
{
	if (!CanAttack())
	{
		// Queue the input if we're attacking but not in combo window yet
		if (bIsAttacking && !bInComboWindow)
		{
			bComboQueued = true;
		}
		return;
	}

	// Determine which attack in the combo
	FAttackData* AttackToUse = nullptr;

	switch (ComboCount)
	{
	case 0:
		AttackToUse = &LightAttack1Data;
		break;
	case 1:
		AttackToUse = &LightAttack2Data;
		break;
	case 2:
		AttackToUse = &LightAttack3Data;
		break;
	default:
		// Reset combo and start over
		ComboCount = 0;
		AttackToUse = &LightAttack1Data;
		break;
	}

	if (AttackToUse)
	{
		ExecuteAttack(*AttackToUse);
		ComboCount++;
	}
}

void UCombatComponent::RequestHeavyAttack()
{
	if (!CanAttack())
	{
		return;
	}

	// Start charging
	bChargingHeavy = true;
	CurrentChargeTime = 0.0f;

	UE_LOG(LogVerdantHeart, Log, TEXT("Started charging heavy attack"));
}

void UCombatComponent::ReleaseHeavyAttack()
{
	if (!bChargingHeavy)
	{
		return;
	}

	bChargingHeavy = false;

	// Determine if fully charged
	if (CurrentChargeTime >= ChargeTimeForFullCharge)
	{
		ExecuteAttack(ChargedHeavyAttackData);
		UE_LOG(LogVerdantHeart, Log, TEXT("Released CHARGED heavy attack"));
	}
	else
	{
		ExecuteAttack(HeavyAttackData);
		UE_LOG(LogVerdantHeart, Log, TEXT("Released normal heavy attack"));
	}

	CurrentChargeTime = 0.0f;

	// Heavy attacks reset combo
	ResetCombo();
}

void UCombatComponent::RequestDodgeAttack()
{
	if (!CanAttack())
	{
		return;
	}

	ExecuteAttack(DodgeAttackData);
}

void UCombatComponent::ExecuteAttack(const FAttackData& AttackData)
{
	bIsAttacking = true;
	bInComboWindow = false;
	bComboQueued = false;
	CurrentAttackType = AttackData.AttackType;
	CurrentAttackData = AttackData;

	UE_LOG(LogVerdantHeart, Log, TEXT("Executing attack: %d, Damage: %.1f"), 
		(int32)AttackData.AttackType, AttackData.Damage);

	OnAttackStarted.Broadcast(AttackData.AttackType);

	// Play animation montage if set
	if (AttackData.AttackMontage)
	{
		if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
		{
			Character->PlayAnimMontage(AttackData.AttackMontage);
		}
	}
}

void UCombatComponent::EnableHitDetection()
{
	bHitDetectionEnabled = true;
	HitActorsThisSwing.Empty();

	UE_LOG(LogVerdantHeart, Verbose, TEXT("Hit detection enabled"));
}

void UCombatComponent::DisableHitDetection()
{
	bHitDetectionEnabled = false;
	HitActorsThisSwing.Empty();

	UE_LOG(LogVerdantHeart, Verbose, TEXT("Hit detection disabled"));
}

void UCombatComponent::PerformHitDetection()
{
	if (!OwnerMesh)
	{
		return;
	}

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	// Get attack origin - either from socket or owner location
	FVector AttackOrigin;
	if (OwnerMesh->DoesSocketExist(WeaponSocketName))
	{
		AttackOrigin = OwnerMesh->GetSocketLocation(WeaponSocketName);
	}
	else
	{
		AttackOrigin = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 50.0f;
	}

	// Calculate end point
	FVector AttackEnd = AttackOrigin + Owner->GetActorForwardVector() * CurrentAttackData.Range;

	// Perform sphere sweep
	TArray<FHitResult> HitResults;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner);

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		AttackOrigin,
		AttackEnd,
		FQuat::Identity,
		ECC_EnemyHitable,
		FCollisionShape::MakeSphere(CurrentAttackData.AttackRadius),
		QueryParams
	);

	// Process hits
	for (const FHitResult& Hit : HitResults)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor && !HitActorsThisSwing.Contains(HitActor))
		{
			// Haven't hit this actor this swing yet
			HitActorsThisSwing.Add(HitActor);
			ApplyDamageToTarget(HitActor, CurrentAttackData.Damage);
		}
	}

	// Debug visualization
#if WITH_EDITOR
	DrawDebugLine(GetWorld(), AttackOrigin, AttackEnd, bHit ? FColor::Green : FColor::Red, false, 0.1f);
	DrawDebugSphere(GetWorld(), AttackEnd, CurrentAttackData.AttackRadius, 8, bHit ? FColor::Green : FColor::Red, false, 0.1f);
#endif
}

void UCombatComponent::ApplyDamageToTarget(AActor* Target, float Damage)
{
	if (!Target)
	{
		return;
	}

	UE_LOG(LogVerdantHeart, Log, TEXT("Dealing %.1f damage to %s"), Damage, *Target->GetName());

	// Apply damage using Unreal's damage system
	UGameplayStatics::ApplyDamage(
		Target,
		Damage,
		GetOwner()->GetInstigatorController(),
		GetOwner(),
		nullptr // DamageType - can be customized
	);

	OnDamageDealt.Broadcast(Target, Damage);
}

void UCombatComponent::OnAttackMontageEnded()
{
	bIsAttacking = false;
	bInComboWindow = false;

	OnAttackEnded.Broadcast(CurrentAttackType);

	// Check if combo input was queued
	if (bComboQueued)
	{
		bComboQueued = false;
		RequestLightAttack();
	}

	CurrentAttackType = EAttackType::None;
}

void UCombatComponent::OpenComboWindow()
{
	bInComboWindow = true;

	UE_LOG(LogVerdantHeart, Verbose, TEXT("Combo window opened"));

	// If input was queued, process it now
	if (bComboQueued)
	{
		bComboQueued = false;
		RequestLightAttack();
	}
}

void UCombatComponent::CloseComboWindow()
{
	if (bInComboWindow && !bComboQueued)
	{
		// Window closed without combo input - reset
		ResetCombo();
	}
	bInComboWindow = false;

	UE_LOG(LogVerdantHeart, Verbose, TEXT("Combo window closed"));
}

void UCombatComponent::ResetCombo()
{
	ComboCount = 0;
	bComboQueued = false;

	OnComboReset.Broadcast();

	UE_LOG(LogVerdantHeart, Log, TEXT("Combo reset"));
}

// CollectibleBase.cpp

#include "Gameplay/CollectibleBase.h"
#include "Characters/VerdantHeartCharacter.h"
#include "VerdantHeart.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// ============================================================================
// COLLECTIBLE BASE
// ============================================================================

ACollectibleBase::ACollectibleBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetSphereRadius(100.0f);
	CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));

	IdleVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("IdleVFX"));
	IdleVFX->SetupAttachment(RootComponent);
}

void ACollectibleBase::BeginPlay()
{
	Super::BeginPlay();

	// Bind overlap event
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACollectibleBase::OnOverlapBegin);

	// Generate ID if not set
	if (CollectibleID.IsNone())
	{
		CollectibleID = FName(*FString::Printf(TEXT("Collectible_%s"), *GetName()));
	}
}

void ACollectibleBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if player
	if (AVerdantHeartCharacter* Player = Cast<AVerdantHeartCharacter>(OtherActor))
	{
		Collect(Player);
	}
}

void ACollectibleBase::Collect(AActor* Collector)
{
	if (bIsCollected)
	{
		return;
	}

	bIsCollected = true;

	UE_LOG(LogVerdantHeart, Log, TEXT("Collectible %s picked up by %s"), 
		*CollectibleID.ToString(), *Collector->GetName());

	// Play sound
	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	}

	// Spawn pickup VFX
	if (PickupVFX)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this, PickupVFX, GetActorLocation(), GetActorRotation());
	}

	// Broadcast event
	OnCollectiblePickedUp.Broadcast(this, Collector, CollectibleType);

	// Call Blueprint event
	OnCollected(Collector);

	// Destroy or hide
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

// ============================================================================
// SPIRIT ESSENCE
// ============================================================================

ASpiritEssence::ASpiritEssence()
{
	PrimaryActorTick.bCanEverTick = true;
	CollectibleType = ECollectibleType::SpiritEssence;
}

void ASpiritEssence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsCollected)
	{
		return;
	}

	// Bob animation
	BobTime += DeltaTime * BobSpeed;
	float BobOffset = FMath::Sin(BobTime) * BobHeight;
	
	FVector NewLocation = InitialLocation;
	NewLocation.Z += BobOffset;
	SetActorLocation(NewLocation);

	// Rotation
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += RotationSpeed * DeltaTime;
	SetActorRotation(CurrentRotation);
}

// ============================================================================
// LORE STONE
// ============================================================================

ALoreStone::ALoreStone()
{
	CollectibleType = ECollectibleType::LoreStone;
}

void ALoreStone::ActivateLoreStone(AActor* Activator)
{
	if (bIsCollected)
	{
		return;
	}

	UE_LOG(LogVerdantHeart, Log, TEXT("Lore Stone %s activated"), *CollectibleID.ToString());

	// Play voiceover
	if (LoreVoiceover)
	{
		UGameplayStatics::PlaySound2D(this, LoreVoiceover);
	}

	// Call Blueprint event for UI
	OnLoreStoneActivated(Activator);

	// Mark as collected
	Collect(Activator);
}

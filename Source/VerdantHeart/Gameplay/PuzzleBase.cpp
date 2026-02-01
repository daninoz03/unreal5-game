// PuzzleBase.cpp

#include "Gameplay/PuzzleBase.h"
#include "VerdantHeart.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// ============================================================================
// PUZZLE BASE
// ============================================================================

APuzzleBase::APuzzleBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bAutoActivate = false;
}

void APuzzleBase::BeginPlay()
{
	Super::BeginPlay();
}

void APuzzleBase::Activate_Implementation()
{
	if (bIsSolved)
	{
		return;
	}

	bIsActive = true;
	CurrentActivations++;

	UE_LOG(LogVerdantHeart, Log, TEXT("Puzzle %s activated (%d/%d)"), 
		*GetName(), CurrentActivations, RequiredActivations);

	// Play sound
	if (ActivateSound && AudioComponent)
	{
		AudioComponent->SetSound(ActivateSound);
		AudioComponent->Play();
	}

	OnPuzzleActivated.Broadcast(this);

	// Check if solved
	CheckSolved();

	// Notify connected actors
	NotifyConnectedActors(true);
}

void APuzzleBase::Deactivate_Implementation()
{
	if (bIsSolved)
	{
		return;
	}

	bIsActive = false;
	CurrentActivations = FMath::Max(0, CurrentActivations - 1);

	UE_LOG(LogVerdantHeart, Log, TEXT("Puzzle %s deactivated (%d/%d)"), 
		*GetName(), CurrentActivations, RequiredActivations);

	OnPuzzleDeactivated.Broadcast(this);

	// Notify connected actors
	NotifyConnectedActors(false);
}

bool APuzzleBase::CheckSolved_Implementation()
{
	if (!bIsSolved && CurrentActivations >= RequiredActivations)
	{
		MarkAsSolved();
		return true;
	}
	return bIsSolved;
}

void APuzzleBase::ResetPuzzle_Implementation()
{
	bIsActive = false;
	bIsSolved = false;
	CurrentActivations = 0;

	UE_LOG(LogVerdantHeart, Log, TEXT("Puzzle %s reset"), *GetName());
}

void APuzzleBase::MarkAsSolved()
{
	bIsSolved = true;

	UE_LOG(LogVerdantHeart, Log, TEXT("Puzzle %s SOLVED!"), *GetName());

	// Play solve sound
	if (SolveSound && AudioComponent)
	{
		AudioComponent->SetSound(SolveSound);
		AudioComponent->Play();
	}

	OnPuzzleSolved.Broadcast(this);
}

void APuzzleBase::NotifyConnectedActors(bool bActivate)
{
	for (AActor* ConnectedActor : ConnectedActors)
	{
		if (ConnectedActor)
		{
			// Try to call puzzle door functions
			if (APuzzleDoor* Door = Cast<APuzzleDoor>(ConnectedActor))
			{
				if (bActivate)
				{
					Door->OnPuzzleActivated();
				}
				else
				{
					Door->OnPuzzleDeactivated();
				}
			}
		}
	}
}

// ============================================================================
// PRESSURE PLATE
// ============================================================================

APressurePlate::APressurePlate()
{
	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	PlateMesh->SetupAttachment(RootComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(100.0f, 100.0f, 20.0f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
}

void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	// Bind overlap events
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);
}

void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && !OverlappingActors.Contains(OtherActor))
	{
		OverlappingActors.Add(OtherActor);
		
		// Get weight from actor (player = 70, objects vary)
		float ActorWeight = 70.0f; // Default player weight
		// Could implement IWeightedActor interface for custom weights
		
		CurrentWeight += ActorWeight;
		UpdatePressureState();
	}
}

void APressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OverlappingActors.Contains(OtherActor))
	{
		OverlappingActors.Remove(OtherActor);
		
		float ActorWeight = 70.0f;
		CurrentWeight = FMath::Max(0.0f, CurrentWeight - ActorWeight);
		UpdatePressureState();
	}
}

void APressurePlate::UpdatePressureState()
{
	bool bShouldBeActive = CurrentWeight >= RequiredWeight;

	if (bShouldBeActive && !bIsActive)
	{
		Activate();
	}
	else if (!bShouldBeActive && bIsActive && !bStaysPressed)
	{
		Deactivate();
	}
}

// ============================================================================
// PUZZLE DOOR
// ============================================================================

APuzzleDoor::APuzzleDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);
}

void APuzzleDoor::BeginPlay()
{
	Super::BeginPlay();

	// Store initial position
	ClosedLocation = DoorMesh->GetRelativeLocation();
	OpenLocation = ClosedLocation + OpenOffset;
}

void APuzzleDoor::OnPuzzleActivated()
{
	CurrentActivations++;
	CheckOpenCondition();
}

void APuzzleDoor::OnPuzzleDeactivated()
{
	if (!bStaysOpen)
	{
		CurrentActivations = FMath::Max(0, CurrentActivations - 1);
		CheckOpenCondition();
	}
}

void APuzzleDoor::CheckOpenCondition()
{
	if (CurrentActivations >= RequiredActivations && !bIsOpen)
	{
		OpenDoor();
	}
	else if (CurrentActivations < RequiredActivations && bIsOpen && !bStaysOpen)
	{
		CloseDoor();
	}
}

void APuzzleDoor::OpenDoor()
{
	bIsOpen = true;
	
	// In a real implementation, use a timeline for smooth movement
	DoorMesh->SetRelativeLocation(OpenLocation);
	
	UE_LOG(LogVerdantHeart, Log, TEXT("Door %s opened"), *GetName());
}

void APuzzleDoor::CloseDoor()
{
	bIsOpen = false;
	
	DoorMesh->SetRelativeLocation(ClosedLocation);
	
	UE_LOG(LogVerdantHeart, Log, TEXT("Door %s closed"), *GetName());
}

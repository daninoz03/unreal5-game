// InteractableBase.cpp

#include "Gameplay/InteractableBase.h"
#include "VerdantHeart.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

AInteractableBase::AInteractableBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create root component
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	// Create mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionProfileName(TEXT("BlockAll"));

	// Create interaction trigger
	InteractionTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionTrigger"));
	InteractionTrigger->SetupAttachment(RootComponent);
	InteractionTrigger->SetSphereRadius(InteractionRange);
	InteractionTrigger->SetCollisionProfileName(TEXT("Trigger"));
	InteractionTrigger->SetCollisionResponseToChannel(ECC_Interactable, ECR_Block);
}

void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	// Update trigger radius
	if (InteractionTrigger)
	{
		InteractionTrigger->SetSphereRadius(InteractionRange);
	}
}

bool AInteractableBase::CanInteract_Implementation(AActor* Interactor) const
{
	if (!Interactor)
	{
		return false;
	}

	// Check if already interacted and not repeatable
	if (bHasBeenInteracted && !bCanInteractMultipleTimes)
	{
		return false;
	}

	// Check distance
	float Distance = FVector::Dist(GetActorLocation(), Interactor->GetActorLocation());
	return Distance <= InteractionRange;
}

void AInteractableBase::Interact_Implementation(AActor* Interactor)
{
	if (!CanInteract(Interactor))
	{
		return;
	}

	bHasBeenInteracted = true;

	UE_LOG(LogVerdantHeart, Log, TEXT("%s interacted with %s"), 
		*Interactor->GetName(), *GetName());

	// Broadcast event
	OnInteracted.Broadcast(Interactor, this);
}

FText AInteractableBase::GetInteractionPrompt_Implementation() const
{
	return InteractionPromptText;
}

void AInteractableBase::SetHighlighted(bool bNewHighlighted)
{
	if (bIsHighlighted != bNewHighlighted)
	{
		bIsHighlighted = bNewHighlighted;
		OnHighlightChanged(bNewHighlighted);
	}
}

// InteractableBase.h - Base class for all interactable objects

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

// Interaction type enum
UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	Use,        // Generic use (levers, buttons)
	Pickup,     // Collectibles
	Examine,    // Lore stones, environmental storytelling
	Talk,       // NPCs (if any)
	Push        // Pushable objects
};

// Delegate for interaction events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteracted, AActor*, Interactor, AInteractableBase*, Interactable);

UCLASS(Abstract)
class VERDANTHEART_API AInteractableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractableBase();

	// Check if interaction is possible
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	bool CanInteract(AActor* Interactor) const;

	// Perform the interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(AActor* Interactor);

	// Get interaction prompt text
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FText GetInteractionPrompt() const;

	// Get interaction type
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	EInteractionType GetInteractionType() const { return InteractionType; }

	// Enable/disable highlight (for focus mode)
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetHighlighted(bool bNewHighlighted);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool IsHighlighted() const { return bIsHighlighted; }

	// Event when interacted
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteracted OnInteracted;

protected:
	virtual void BeginPlay() override;

	// Called when highlight state changes - implement visual feedback in Blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnHighlightChanged(bool bNewHighlighted);

	// ---- COMPONENTS ----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* InteractionTrigger;

	// ---- SETTINGS ----

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	EInteractionType InteractionType = EInteractionType::Use;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	FText InteractionPromptText = FText::FromString("Interact");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	float InteractionRange = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	bool bCanInteractMultipleTimes = true;

	// ---- STATE ----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bHasBeenInteracted = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsHighlighted = false;
};

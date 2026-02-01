// CollectibleBase.h - Base class for all collectibles

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectibleBase.generated.h"

// Collectible type enum
UENUM(BlueprintType)
enum class ECollectibleType : uint8
{
	SpiritEssence,
	LoreStone,
	GuardianRelic
};

// Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCollectiblePickedUp, ACollectibleBase*, Collectible, AActor*, Collector, ECollectibleType, Type);

UCLASS(Abstract)
class VERDANTHEART_API ACollectibleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectibleBase();

	// Get collectible info
	UFUNCTION(BlueprintCallable, Category = "Collectible")
	FName GetCollectibleID() const { return CollectibleID; }

	UFUNCTION(BlueprintCallable, Category = "Collectible")
	ECollectibleType GetCollectibleType() const { return CollectibleType; }

	UFUNCTION(BlueprintCallable, Category = "Collectible")
	bool IsCollected() const { return bIsCollected; }

	// Collect this item
	UFUNCTION(BlueprintCallable, Category = "Collectible")
	void Collect(AActor* Collector);

	// Event
	UPROPERTY(BlueprintAssignable, Category = "Collectible")
	FOnCollectiblePickedUp OnCollectiblePickedUp;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when collected - implement visual feedback in Blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "Collectible")
	void OnCollected(AActor* Collector);

	// ---- COMPONENTS ----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UNiagaraComponent* IdleVFX;

	// ---- SETTINGS ----

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectible")
	FName CollectibleID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collectible")
	ECollectibleType CollectibleType = ECollectibleType::SpiritEssence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collectible")
	class USoundCue* PickupSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collectible")
	class UNiagaraSystem* PickupVFX;

	// ---- STATE ----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsCollected = false;
};

// ============================================================================
// SPIRIT ESSENCE
// ============================================================================

UCLASS()
class VERDANTHEART_API ASpiritEssence : public ACollectibleBase
{
	GENERATED_BODY()

public:
	ASpiritEssence();

	virtual void Tick(float DeltaTime) override;

protected:
	// Floating animation
	UPROPERTY(EditDefaultsOnly, Category = "Spirit Essence")
	float BobHeight = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Spirit Essence")
	float BobSpeed = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Spirit Essence")
	float RotationSpeed = 50.0f;

	FVector InitialLocation;
	float BobTime = 0.0f;
};

// ============================================================================
// LORE STONE
// ============================================================================

UCLASS()
class VERDANTHEART_API ALoreStone : public ACollectibleBase
{
	GENERATED_BODY()

public:
	ALoreStone();

	// Activate the lore stone (plays audio/shows text)
	UFUNCTION(BlueprintCallable, Category = "Lore Stone")
	void ActivateLoreStone(AActor* Activator);

	// Get lore content
	UFUNCTION(BlueprintCallable, Category = "Lore Stone")
	const FText& GetLoreTitle() const { return LoreTitle; }

	UFUNCTION(BlueprintCallable, Category = "Lore Stone")
	const FText& GetLoreContent() const { return LoreContent; }

protected:
	// Called when activated - implement in Blueprint for UI display
	UFUNCTION(BlueprintImplementableEvent, Category = "Lore Stone")
	void OnLoreStoneActivated(AActor* Activator);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lore Stone", meta=(MultiLine=true))
	FText LoreTitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lore Stone", meta=(MultiLine=true))
	FText LoreContent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lore Stone")
	class USoundCue* LoreVoiceover;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lore Stone")
	float VoiceoverDuration = 10.0f;
};

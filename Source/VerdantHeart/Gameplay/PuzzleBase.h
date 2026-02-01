// PuzzleBase.h - Base class for puzzle elements

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleBase.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPuzzleActivated, APuzzleBase*, Puzzle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPuzzleDeactivated, APuzzleBase*, Puzzle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPuzzleSolved, APuzzleBase*, Puzzle);

UCLASS(Abstract)
class VERDANTHEART_API APuzzleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APuzzleBase();

	// Activate the puzzle element
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Puzzle")
	void Activate();

	// Deactivate the puzzle element
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Puzzle")
	void Deactivate();

	// Check if puzzle is solved
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Puzzle")
	bool CheckSolved();

	// Reset the puzzle to initial state
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Puzzle")
	void ResetPuzzle();

	// State queries
	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	bool IsActive() const { return bIsActive; }

	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	bool IsSolved() const { return bIsSolved; }

	// Events
	UPROPERTY(BlueprintAssignable, Category = "Puzzle")
	FOnPuzzleActivated OnPuzzleActivated;

	UPROPERTY(BlueprintAssignable, Category = "Puzzle")
	FOnPuzzleDeactivated OnPuzzleDeactivated;

	UPROPERTY(BlueprintAssignable, Category = "Puzzle")
	FOnPuzzleSolved OnPuzzleSolved;

protected:
	virtual void BeginPlay() override;

	// Mark puzzle as solved - call this when solution is reached
	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void MarkAsSolved();

	// Notify connected actors
	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void NotifyConnectedActors(bool bActivate);

	// ---- COMPONENTS ----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UAudioComponent* AudioComponent;

	// ---- SETTINGS ----

	// Actors to notify when this puzzle changes state (doors, platforms, etc.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TArray<AActor*> ConnectedActors;

	// How many activations needed to solve (for multi-part puzzles)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Puzzle")
	int32 RequiredActivations = 1;

	// Sound to play when activated
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Puzzle|Audio")
	class USoundCue* ActivateSound;

	// Sound to play when solved
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Puzzle|Audio")
	USoundCue* SolveSound;

	// ---- STATE ----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsActive = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsSolved = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	int32 CurrentActivations = 0;
};

// ============================================================================
// PRESSURE PLATE
// ============================================================================

UCLASS()
class VERDANTHEART_API APressurePlate : public APuzzleBase
{
	GENERATED_BODY()

public:
	APressurePlate();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void UpdatePressureState();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* PlateMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* TriggerBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pressure Plate")
	float RequiredWeight = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pressure Plate")
	bool bStaysPressed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float CurrentWeight = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	TArray<AActor*> OverlappingActors;
};

// ============================================================================
// PUZZLE DOOR
// ============================================================================

UCLASS()
class VERDANTHEART_API APuzzleDoor : public AActor
{
	GENERATED_BODY()

public:
	APuzzleDoor();

	// Open/close the door
	UFUNCTION(BlueprintCallable, Category = "Door")
	void OpenDoor();

	UFUNCTION(BlueprintCallable, Category = "Door")
	void CloseDoor();

	UFUNCTION(BlueprintCallable, Category = "Door")
	bool IsOpen() const { return bIsOpen; }

	// Called by connected puzzle elements
	UFUNCTION(BlueprintCallable, Category = "Door")
	void OnPuzzleActivated();

	UFUNCTION(BlueprintCallable, Category = "Door")
	void OnPuzzleDeactivated();

protected:
	virtual void BeginPlay() override;

	void CheckOpenCondition();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door")
	int32 RequiredActivations = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door")
	bool bStaysOpen = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door")
	FVector OpenOffset = FVector(0.0f, 0.0f, 300.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door")
	float OpenSpeed = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsOpen = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	int32 CurrentActivations = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	FVector ClosedLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	FVector OpenLocation;
};

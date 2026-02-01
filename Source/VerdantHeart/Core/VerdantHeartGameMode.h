// VerdantHeartGameMode.h - Main game mode handling checkpoints, respawn, etc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VerdantHeartGameMode.generated.h"

// Forward declarations
class ACheckpointActor;
class AVerdantHeartCharacter;

// Game state enum
UENUM(BlueprintType)
enum class EGameState : uint8
{
	MainMenu,
	Loading,
	Playing,
	Paused,
	Cutscene,
	Death,
	Victory
};

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameStateChanged, EGameState, NewState, EGameState, OldState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCheckpointReached, ACheckpointActor*, Checkpoint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerRespawn);

UCLASS()
class VERDANTHEART_API AVerdantHeartGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AVerdantHeartGameMode();

	// Game state management
	UFUNCTION(BlueprintCallable, Category = "Game State")
	EGameState GetGameState() const { return CurrentGameState; }

	UFUNCTION(BlueprintCallable, Category = "Game State")
	void SetGameState(EGameState NewState);

	// Checkpoint system
	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void RegisterCheckpoint(ACheckpointActor* Checkpoint);

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	ACheckpointActor* GetCurrentCheckpoint() const { return CurrentCheckpoint; }

	// Player death/respawn
	UFUNCTION(BlueprintCallable, Category = "Player")
	void OnPlayerDied();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void RespawnPlayer();

	// Events
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGameStateChanged OnGameStateChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCheckpointReached OnCheckpointReached;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPlayerDeath OnPlayerDeathEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPlayerRespawn OnPlayerRespawnEvent;

protected:
	virtual void BeginPlay() override;

	// Respawn implementation
	void PerformRespawn();

	// ---- STATE ----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	EGameState CurrentGameState = EGameState::Playing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	ACheckpointActor* CurrentCheckpoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	AVerdantHeartCharacter* PlayerCharacter;

	// ---- SETTINGS ----

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	float RespawnDelay = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	TSubclassOf<AVerdantHeartCharacter> PlayerCharacterClass;

	// Timer for respawn
	FTimerHandle RespawnTimerHandle;
};

// ============================================================================
// CHECKPOINT ACTOR
// ============================================================================

UCLASS()
class VERDANTHEART_API ACheckpointActor : public AActor
{
	GENERATED_BODY()

public:
	ACheckpointActor();

	// Get spawn transform for respawning
	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	FTransform GetSpawnTransform() const;

	// Get checkpoint ID
	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	FName GetCheckpointID() const { return CheckpointID; }

	// Check if activated
	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	bool IsActivated() const { return bIsActivated; }

	// Activate checkpoint (called when player enters)
	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void ActivateCheckpoint();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Visual feedback - implement in Blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "Checkpoint")
	void OnCheckpointActivated();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* TriggerVolume;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Checkpoint")
	FName CheckpointID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Checkpoint")
	bool bAutoSave = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsActivated = false;
};

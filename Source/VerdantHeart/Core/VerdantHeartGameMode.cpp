// VerdantHeartGameMode.cpp

#include "Core/VerdantHeartGameMode.h"
#include "Characters/VerdantHeartCharacter.h"
#include "VerdantHeart.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// ============================================================================
// GAME MODE
// ============================================================================

AVerdantHeartGameMode::AVerdantHeartGameMode()
{
	// Set default pawn class - can be overridden in Blueprint
	DefaultPawnClass = AVerdantHeartCharacter::StaticClass();
}

void AVerdantHeartGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Get player character reference
	PlayerCharacter = Cast<AVerdantHeartCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	SetGameState(EGameState::Playing);

	UE_LOG(LogVerdantHeart, Log, TEXT("VerdantHeartGameMode initialized"));
}

void AVerdantHeartGameMode::SetGameState(EGameState NewState)
{
	if (CurrentGameState != NewState)
	{
		EGameState OldState = CurrentGameState;
		CurrentGameState = NewState;

		UE_LOG(LogVerdantHeart, Log, TEXT("Game state changed: %d -> %d"), (int32)OldState, (int32)NewState);

		// Handle state-specific logic
		switch (NewState)
		{
		case EGameState::Paused:
			UGameplayStatics::SetGamePaused(this, true);
			break;
		case EGameState::Playing:
			UGameplayStatics::SetGamePaused(this, false);
			break;
		case EGameState::Death:
			// Death state handling done in OnPlayerDied
			break;
		default:
			break;
		}

		OnGameStateChanged.Broadcast(NewState, OldState);
	}
}

void AVerdantHeartGameMode::RegisterCheckpoint(ACheckpointActor* Checkpoint)
{
	if (Checkpoint && Checkpoint != CurrentCheckpoint)
	{
		CurrentCheckpoint = Checkpoint;
		
		UE_LOG(LogVerdantHeart, Log, TEXT("Checkpoint registered: %s"), *Checkpoint->GetCheckpointID().ToString());
		
		OnCheckpointReached.Broadcast(Checkpoint);
	}
}

void AVerdantHeartGameMode::OnPlayerDied()
{
	UE_LOG(LogVerdantHeart, Log, TEXT("Player died - starting respawn sequence"));

	SetGameState(EGameState::Death);
	OnPlayerDeathEvent.Broadcast();

	// Start respawn timer
	GetWorldTimerManager().SetTimer(
		RespawnTimerHandle,
		this,
		&AVerdantHeartGameMode::PerformRespawn,
		RespawnDelay,
		false
	);
}

void AVerdantHeartGameMode::RespawnPlayer()
{
	// Clear timer if manually respawning
	GetWorldTimerManager().ClearTimer(RespawnTimerHandle);
	PerformRespawn();
}

void AVerdantHeartGameMode::PerformRespawn()
{
	FTransform SpawnTransform;

	// Get spawn location from checkpoint or default
	if (CurrentCheckpoint)
	{
		SpawnTransform = CurrentCheckpoint->GetSpawnTransform();
	}
	else
	{
		// Use default player start
		AActor* PlayerStart = FindPlayerStart(GetWorld()->GetFirstPlayerController());
		if (PlayerStart)
		{
			SpawnTransform = PlayerStart->GetActorTransform();
		}
	}

	// Respawn or reset player
	if (PlayerCharacter)
	{
		// Reset player state
		PlayerCharacter->SetActorTransform(SpawnTransform);
		
		// Reset health
		if (UHealthComponent* HealthComp = PlayerCharacter->GetHealthComponent())
		{
			HealthComp->Heal(HealthComp->GetMaxHealth());
		}

		// Re-enable input
		PlayerCharacter->EnableInput(Cast<APlayerController>(PlayerCharacter->GetController()));
	}

	SetGameState(EGameState::Playing);
	OnPlayerRespawnEvent.Broadcast();

	UE_LOG(LogVerdantHeart, Log, TEXT("Player respawned at %s"), *SpawnTransform.GetLocation().ToString());
}

// ============================================================================
// CHECKPOINT ACTOR
// ============================================================================

ACheckpointActor::ACheckpointActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(RootComponent);
	TriggerVolume->SetBoxExtent(FVector(100.0f, 100.0f, 200.0f));
	TriggerVolume->SetCollisionProfileName(TEXT("Trigger"));
}

void ACheckpointActor::BeginPlay()
{
	Super::BeginPlay();

	// Bind overlap event
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointActor::OnOverlapBegin);

	// Generate ID if not set
	if (CheckpointID.IsNone())
	{
		CheckpointID = FName(*FString::Printf(TEXT("Checkpoint_%s"), *GetName()));
	}
}

void ACheckpointActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if player
	if (AVerdantHeartCharacter* Player = Cast<AVerdantHeartCharacter>(OtherActor))
	{
		ActivateCheckpoint();
	}
}

void ACheckpointActor::ActivateCheckpoint()
{
	if (bIsActivated)
	{
		return;
	}

	bIsActivated = true;

	UE_LOG(LogVerdantHeart, Log, TEXT("Checkpoint %s activated"), *CheckpointID.ToString());

	// Register with game mode
	if (AVerdantHeartGameMode* GameMode = Cast<AVerdantHeartGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->RegisterCheckpoint(this);
	}

	// Visual feedback
	OnCheckpointActivated();

	// Auto-save if enabled
	if (bAutoSave)
	{
		// TODO: Call save game on game instance
	}
}

FTransform ACheckpointActor::GetSpawnTransform() const
{
	return GetActorTransform();
}

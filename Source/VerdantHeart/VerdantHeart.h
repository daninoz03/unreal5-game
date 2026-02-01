// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Log category for the game
DECLARE_LOG_CATEGORY_EXTERN(LogVerdantHeart, Log, All);

// Collision channels
#define ECC_Climbable ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Interactable ECollisionChannel::ECC_GameTraceChannel2
#define ECC_EnemyHitable ECollisionChannel::ECC_GameTraceChannel3

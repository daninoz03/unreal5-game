# 🔧 C++ Setup Guide

**How to integrate the C++ base classes into your UE5 project**

---

## Overview

This project includes C++ base classes that you'll extend with Blueprints. This gives you:
- **Performance**: C++ core with Blueprint flexibility
- **Reusability**: Base classes handle common logic
- **Extensibility**: Override functions in Blueprint for customization

---

## Step 1: Create UE5 Project

1. Open Unreal Engine 5.3+
2. Create **New Project** → **Games** → **Blank**
3. Settings:
   - **Project Name**: `VerdantHeart`
   - **C++** (not Blueprint)
   - **No Starter Content** (we'll add what we need)
4. Click Create

---

## Step 2: Copy Source Files

1. Close the Unreal Editor
2. Copy the entire `Source/VerdantHeart/` folder from this repo
3. Paste it into your project's `Source/` folder, replacing the generated files
4. Your structure should look like:

```
VerdantHeart/
├── Source/
│   └── VerdantHeart/
│       ├── VerdantHeart.Build.cs
│       ├── VerdantHeart.h
│       ├── VerdantHeart.cpp
│       ├── Characters/
│       │   ├── VerdantHeartCharacter.h
│       │   └── VerdantHeartCharacter.cpp
│       ├── Components/
│       │   ├── HealthComponent.h
│       │   ├── HealthComponent.cpp
│       │   ├── CombatComponent.h
│       │   └── CombatComponent.cpp
│       ├── Enemies/
│       │   ├── EnemyBase.h
│       │   └── EnemyBase.cpp
│       ├── Gameplay/
│       │   ├── InteractableBase.h
│       │   ├── InteractableBase.cpp
│       │   ├── PuzzleBase.h
│       │   ├── PuzzleBase.cpp
│       │   ├── CollectibleBase.h
│       │   └── CollectibleBase.cpp
│       └── Core/
│           ├── VerdantHeartGameMode.h
│           └── VerdantHeartGameMode.cpp
├── Content/
└── ...
```

---

## Step 3: Regenerate Project Files

1. Right-click on `VerdantHeart.uproject`
2. Select **Generate Visual Studio project files** (Windows) or **Generate Xcode project** (Mac)
3. Wait for generation to complete

---

## Step 4: Build the Project

### Option A: From Editor
1. Open the project in Unreal Editor
2. It will prompt to build - click Yes
3. Wait for compilation (first time takes several minutes)

### Option B: From IDE
1. Open `VerdantHeart.sln` in Visual Studio (or Xcode on Mac)
2. Build the project (F7 or Cmd+B)
3. Then open in Unreal Editor

---

## Step 5: Create Blueprint Children

Now create Blueprint classes that extend the C++ base classes:

### Player Character
1. Content Browser → Right-click → Blueprint Class
2. Search for `VerdantHeartCharacter`
3. Select it as parent
4. Name: `BP_Kira`

### Configure BP_Kira:
- **Input Actions**: Create and assign Input Actions in the Details panel
- **Animation**: Set up Animation Blueprint
- **Mesh**: Assign skeletal mesh

### Enemies
1. Create Blueprint extending `EnemyBase`
2. Name: `BP_BlightedWolf`
3. Set `BehaviorTree`, `AttackMontage`, stats

### Puzzles
1. Create Blueprint extending `PressurePlate`
2. Create Blueprint extending `PuzzleDoor`
3. Connect them in the level

---

## Step 6: Set Up Input Actions

Create these Input Actions in `Content/VerdantHeart/Input/`:

| Input Action | Value Type |
|--------------|------------|
| `IA_Move` | Axis2D (Vector2D) |
| `IA_Look` | Axis2D (Vector2D) |
| `IA_Jump` | Digital (Bool) |
| `IA_Sprint` | Digital (Bool) |
| `IA_Dodge` | Digital (Bool) |
| `IA_LightAttack` | Digital (Bool) |
| `IA_HeavyAttack` | Digital (Bool) |
| `IA_Interact` | Digital (Bool) |
| `IA_Focus` | Digital (Bool) |

Then create `IMC_Default` Input Mapping Context and map them.

---

## Step 7: Import Data Tables

1. In Content Browser, right-click → Import
2. Select the CSV files from `Data/` folder
3. When prompted for row type:
   - `DT_EnemyStats.csv` → Create new struct or use custom
   - `DT_AttackData.csv` → Create new struct
   - `DT_Collectibles.csv` → Create new struct

---

## Class Reference

### Components (Add to any Actor)

| Component | Purpose |
|-----------|---------|
| `UHealthComponent` | Health, damage, death handling |
| `UCombatComponent` | Attacks, combos, hit detection |

### Characters

| Class | Purpose | Extend With |
|-------|---------|-------------|
| `AVerdantHeartCharacter` | Player character | `BP_Kira` |
| `AEnemyBase` | Base enemy | `BP_BlightedWolf`, `BP_Treant` |

### Gameplay

| Class | Purpose | Extend With |
|-------|---------|-------------|
| `AInteractableBase` | Interactable objects | Levers, doors |
| `APuzzleBase` | Puzzle elements | Custom puzzles |
| `APressurePlate` | Pressure plate | Ready to use |
| `APuzzleDoor` | Puzzle-controlled door | Ready to use |
| `ACollectibleBase` | Collectibles | - |
| `ASpiritEssence` | Floating essence | Ready to use |
| `ALoreStone` | Lore collectible | Ready to use |

### Core

| Class | Purpose |
|-------|---------|
| `AVerdantHeartGameMode` | Game flow, checkpoints |
| `ACheckpointActor` | Checkpoint volumes |

---

## Blueprint Extension Examples

### Extending EnemyBase for Wolf

In `BP_BlightedWolf`:

1. Set default values:
   - `MaxHealth`: 40
   - `AttackDamage`: 15
   - `AttackRange`: 150
   - `DetectionRange`: 1000

2. Override `HandleDeath`:
   - Play death animation
   - Spawn death VFX
   - Call parent function

3. Set up AI:
   - Assign Behavior Tree
   - Create AI Controller

### Extending PuzzleBase for Beam Mirror

1. Create `BP_BeamMirror` extending `APuzzleBase`
2. Add Static Mesh for mirror visual
3. Add custom rotation logic
4. Override `Activate` for beam redirection

---

## Debugging Tips

### Enable Logging
The code uses `UE_LOG(LogVerdantHeart, ...)`. View in Output Log.

### Visual Debug
Combat hit detection draws debug lines in editor. Disable for shipping:
```cpp
#if WITH_EDITOR
    DrawDebugLine(...)
#endif
```

### Common Issues

| Issue | Solution |
|-------|----------|
| "Unresolved external" | Rebuild solution, check includes |
| Blueprint won't compile | Check parent class compiles first |
| Input not working | Verify Input Mapping Context is added |
| AI not moving | Build NavMesh (P key in editor) |

---

## Next Steps

1. ✅ Copy Source files
2. ✅ Build project
3. ⬜ Create BP_Kira (player)
4. ⬜ Set up Input Actions
5. ⬜ Create BP_BlightedWolf
6. ⬜ Test in empty level
7. ⬜ Build first area

---

*The C++ base classes handle the heavy lifting. Blueprints let you customize and iterate quickly.*

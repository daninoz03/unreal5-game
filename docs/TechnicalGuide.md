# 🔧 Technical Implementation Guide

**Document Version**: 1.0  
**Engine Version**: Unreal Engine 5.3+  
**Project Type**: Third-Person Game (Blueprint)  

---

## Table of Contents

1. [Initial Setup](#initial-setup)
2. [Project Settings](#project-settings)
3. [Folder Structure](#folder-structure)
4. [Implementation Order](#implementation-order)
5. [Blueprint Setup](#blueprint-setup)
6. [Level Setup](#level-setup)
7. [Common Issues](#common-issues)
8. [Performance Tips](#performance-tips)
9. [Resources & Learning](#resources--learning)

---

## Initial Setup

### Prerequisites

| Requirement | Minimum | Recommended |
|-------------|---------|-------------|
| **OS** | Windows 10 | Windows 11 |
| **RAM** | 16 GB | 32 GB |
| **GPU** | GTX 1070 | RTX 3060+ |
| **Storage** | 100 GB SSD | 200 GB NVMe |
| **CPU** | 6 cores | 8+ cores |

### Installing Unreal Engine 5

1. Download **Epic Games Launcher** from [unrealengine.com](https://www.unrealengine.com/download)
2. Sign in / Create account
3. Go to **Unreal Engine** tab → **Library**
4. Click **+** button → Select **5.3** or latest 5.x version
5. Install (approximately 50-100 GB)

### Creating the Project

1. Launch UE5
2. Select **Games** category
3. Choose **Third Person** template
4. Configure:
   - **Project Name**: `VerdantHeart`
   - **Location**: Your cloned repo folder (`unreal5-game/`)
   - **Blueprint** (not C++)
   - **Starter Content**: Yes (helpful for prototyping)
   - **Raytracing**: Optional (performance impact)
5. Click **Create**

---

## Project Settings

After creating the project, configure these settings:

### Project → Description
```
Project Name: Verdant Heart
Description: Third-person action-adventure in a mystical forest
Project Version: 0.1.0
```

### Project → Maps & Modes

| Setting | Value |
|---------|-------|
| Default GameMode | GM_VerdantHeart (create first) |
| Editor Startup Map | L_VerdantHeart_Persistent |
| Game Default Map | L_MainMenu |

### Engine → Input

**Enable Enhanced Input System:**
1. Edit → Project Settings → Engine → Input
2. Set **Default Player Input Class** to `EnhancedPlayerInput`
3. Set **Default Input Component Class** to `EnhancedInputComponent`

### Engine → Rendering (Optional)

For best visuals:
| Setting | Value |
|---------|-------|
| Global Illumination | Lumen |
| Reflections | Lumen |
| Shadow Map Method | Virtual Shadow Maps |
| Anti-Aliasing | TSR (Temporal Super Resolution) |

### Engine → Physics

| Setting | Value |
|---------|-------|
| Default Gravity Z | -980 |
| Bounce Threshold Velocity | 100 |

---

## Folder Structure

Organize your Content folder like this:

```
Content/
├── VerdantHeart/
│   ├── Blueprints/
│   │   ├── Characters/
│   │   │   ├── BP_KiraCharacter.uasset
│   │   │   └── ABP_Kira.uasset
│   │   ├── Enemies/
│   │   │   ├── BP_EnemyBase.uasset
│   │   │   ├── BP_BlightedWolf.uasset
│   │   │   └── BP_CorruptedTreant.uasset
│   │   ├── Gameplay/
│   │   │   ├── BP_Checkpoint.uasset
│   │   │   ├── BP_Collectible_Base.uasset
│   │   │   └── BP_InteractableBase.uasset
│   │   ├── Puzzles/
│   │   │   ├── BP_PuzzleBase.uasset
│   │   │   ├── BP_LightSource.uasset
│   │   │   ├── BP_Mirror.uasset
│   │   │   ├── BP_LightReceiver.uasset
│   │   │   ├── BP_PressurePlate.uasset
│   │   │   └── BP_PushableObject.uasset
│   │   ├── Core/
│   │   │   ├── GM_VerdantHeart.uasset
│   │   │   ├── GI_VerdantHeart.uasset
│   │   │   └── PC_VerdantHeart.uasset
│   │   └── AI/
│   │       ├── BT_BlightedWolf.uasset
│   │       ├── BT_Treant.uasset
│   │       └── AIC_EnemyBase.uasset
│   │
│   ├── Maps/
│   │   ├── L_VerdantHeart_Persistent.umap
│   │   ├── L_MainMenu.umap
│   │   ├── L_Area1_SacredGrove.umap
│   │   ├── L_Area2_AncientRuins.umap
│   │   └── L_Area3_HeartOfForest.umap
│   │
│   ├── Characters/
│   │   ├── Kira/
│   │   │   ├── Meshes/
│   │   │   ├── Materials/
│   │   │   ├── Textures/
│   │   │   └── Animations/
│   │   └── Enemies/
│   │       ├── BlightedWolf/
│   │       └── CorruptedTreant/
│   │
│   ├── Environment/
│   │   ├── SacredGrove/
│   │   │   ├── Meshes/
│   │   │   ├── Materials/
│   │   │   └── Textures/
│   │   ├── AncientRuins/
│   │   └── HeartOfForest/
│   │
│   ├── Props/
│   │   ├── Interactables/
│   │   ├── Collectibles/
│   │   └── Puzzles/
│   │
│   ├── VFX/
│   │   ├── Niagara/
│   │   └── Materials/
│   │
│   ├── Audio/
│   │   ├── Music/
│   │   ├── SFX/
│   │   ├── Ambience/
│   │   └── Voice/
│   │
│   ├── UI/
│   │   ├── Widgets/
│   │   ├── Materials/
│   │   └── Textures/
│   │
│   ├── Input/
│   │   ├── IMC_KiraDefault.uasset
│   │   └── InputActions/
│   │
│   └── Data/
│       ├── Enums/
│       ├── Structs/
│       └── DataTables/
│
└── StarterContent/ (can remove later)
```

---

## Implementation Order

Follow this order for smooth development:

### Week 1-2: Foundation

```
Day 1-2: Project Setup
├── Create project
├── Configure settings
├── Set up folder structure
├── Create base blueprints (empty)
└── Test project runs

Day 3-4: Core Character
├── Create BP_KiraCharacter (from Third Person template)
├── Set up Enhanced Input
├── Basic movement (walk, run)
├── Camera setup
└── Test in empty level

Day 5-7: Movement Polish
├── Sprint + Stamina system
├── Jump mechanics
├── Dodge roll
├── Basic animation setup
└── Test all movement
```

### Week 2-3: Core Systems

```
Day 8-10: Combat Foundation
├── Light attack (single)
├── Hit detection
├── Damage system
├── Basic enemy (static target)
└── Test damage dealing

Day 11-12: Combat Polish
├── Light attack combo
├── Heavy attack
├── Enemy health/death
├── Combat feedback (VFX/SFX)
└── Test combat flow

Day 13-14: Enemy AI
├── AI Controller setup
├── Behavior Tree (wolf)
├── Basic patrol
├── Attack behavior
└── Test enemy encounters
```

### Week 3-4: Puzzles & Progression

```
Day 15-16: Puzzle Systems
├── Interactable base
├── Pressure plates
├── Pushable objects
├── Puzzle doors
└── Test puzzle flow

Day 17-18: Beam Puzzles
├── Light source
├── Mirror (rotatable)
├── Light receiver
├── Connect to doors
└── Test beam mechanics

Day 19-21: Game Flow
├── Game Mode setup
├── Checkpoint system
├── Death/Respawn
├── Save system (basic)
└── Test full loop
```

### Week 4+: Content & Polish

```
Day 22-24: First Area (Graybox)
├── Block out Sacred Grove
├── Place gameplay elements
├── Test pacing
├── Iterate on layout
└── First playable!

Day 25-28: Iteration
├── Add remaining areas
├── Polish combat
├── Add collectibles
├── UI implementation
└── Bug fixes

Ongoing: Polish
├── Visual polish
├── Audio implementation
├── VFX passes
├── Playtesting
└── Final adjustments
```

---

## Blueprint Setup

### Creating the Game Mode

1. Right-click in Content Browser
2. Blueprint Class → Game Mode Base
3. Name: `GM_VerdantHeart`
4. Open and set:
   - Default Pawn Class: `BP_KiraCharacter`
   - Player Controller Class: `PC_VerdantHeart`
   - HUD Class: `WBP_HUD`

### Creating the Character

**Option A: Modify Third Person Template**
1. Open `ThirdPersonCharacter` blueprint
2. Rename to `BP_KiraCharacter`
3. Move to your folder structure
4. Modify as per `docs/Blueprints/PlayerController.md`

**Option B: Create From Scratch**
1. Blueprint Class → Character
2. Add components:
   - Capsule (collision)
   - Skeletal Mesh
   - Spring Arm (camera boom)
   - Camera

### Setting Up Enhanced Input

1. **Create Input Actions** (Content/VerdantHeart/Input/InputActions/):
   - `IA_Move` (Vector 2D)
   - `IA_Look` (Vector 2D)
   - `IA_Jump` (Digital)
   - `IA_Dodge` (Digital)
   - `IA_Sprint` (Digital)
   - `IA_Interact` (Digital)
   - `IA_LightAttack` (Digital)
   - `IA_HeavyAttack` (Digital)
   - `IA_Focus` (Digital)

2. **Create Input Mapping Context**:
   - `IMC_KiraDefault`
   - Map all actions to inputs

3. **In Character Blueprint**:
   - On BeginPlay: Add Mapping Context
   - Create input action events

---

## Level Setup

### Persistent Level Structure

```
L_VerdantHeart_Persistent
├── Lighting (Directional Light, Sky)
├── Post Process Volume
├── Game Mode Override: GM_VerdantHeart
├── Player Start
├── Level Streaming Volumes
│   ├── Load_Area1
│   ├── Load_Area2
│   └── Load_Area3
└── Sublevel References
    ├── L_Area1_SacredGrove
    ├── L_Area2_AncientRuins
    └── L_Area3_HeartOfForest
```

### Level Streaming Setup

1. Window → Levels
2. Add Existing → Select area sublevels
3. Set each to "Blueprint" streaming method
4. Use Level Streaming Volumes to trigger loading

### Grayboxing Tips

1. Use **BSP brushes** for quick blockouts
2. Use **Starter Content** geometry for prototyping
3. Keep gameplay metrics in mind:
   - Player height: 180 units
   - Jump height: ~180 units
   - Door width: 200+ units
   - Combat arena: 800+ units
4. Test navigation frequently

---

## Common Issues

### Character Won't Move
- Check Input Mapping Context is added on BeginPlay
- Verify Enhanced Input is enabled in Project Settings
- Check Pawn is possessed by controller

### Camera Issues
- Spring Arm collision settings
- Camera lag too high/low
- Control rotation not linked properly

### Blueprint Compile Errors
- Check for circular references
- Verify all variables have valid references
- Look for null pointer access

### Performance Problems
- Too many tick events (use timers instead)
- Heavy operations every frame
- Unoptimized collision queries
- Too many draw calls (check mesh complexity)

### AI Not Working
- NavMesh not generated (build paths)
- AI Controller not set on enemy
- Behavior Tree not running (check Service)

---

## Performance Tips

### General Guidelines

1. **Avoid Tick when possible**
   - Use Timers for periodic checks
   - Use Event-driven architecture
   - Use Animation Notifies

2. **Optimize Collision**
   - Use simple collision shapes
   - Avoid Mesh collision for dynamic objects
   - Use collision channels appropriately

3. **LOD Everything**
   - Set up LODs for all meshes
   - Use HLOD for large environments
   - Cull distant objects

4. **Profile Regularly**
   - Console command: `stat fps`
   - Console command: `stat unit`
   - Console command: `stat game`
   - Use Unreal Insights

### Blueprint Optimization

```
DO:
✓ Cache component references in variables
✓ Use Functions instead of copy-paste
✓ Use local variables in complex graphs
✓ Break up large blueprints into components

DON'T:
✗ Get component every frame
✗ Use Tick for non-essential updates
✗ Make long blueprint chains (refactor!)
✗ Ignore compilation warnings
```

---

## Resources & Learning

### Official Documentation
- [UE5 Documentation](https://docs.unrealengine.com/)
- [Blueprint Visual Scripting](https://docs.unrealengine.com/5.0/en-US/blueprints-visual-scripting-in-unreal-engine/)
- [Enhanced Input](https://docs.unrealengine.com/5.0/en-US/enhanced-input-in-unreal-engine/)

### YouTube Channels
- **Unreal Engine** (official)
- **Ryan Laley** - Blueprint tutorials
- **Matt Aspland** - Game mechanics
- **Virtus Learning Hub** - Comprehensive tutorials
- **DevEnabled** - Third person tutorials

### Recommended Tutorial Series
1. "UE5 Third Person Game" by Ryan Laley
2. "Blueprint Combat System" by DevEnabled
3. "AI with Behavior Trees" by Matt Aspland
4. "Puzzle Mechanics in UE5" (various)

### Marketplace Assets (Free)
- **Paragon Characters** - High quality characters
- **Infinity Blade Assets** - Weapons, props
- **Open World Demo Collection** - Environment
- **Mixamo Animations** - Free animations

### Communities
- [Unreal Engine Forums](https://forums.unrealengine.com/)
- [r/unrealengine](https://reddit.com/r/unrealengine)
- [Unreal Slackers Discord](https://discord.gg/unreal-slackers)

---

## Quick Reference Commands

### Console Commands
```
stat fps          - Show framerate
stat unit         - Show frame time breakdown
stat game         - Show game thread time
show collision    - Visualize collision
show navigation   - Show navmesh
slomo 0.5         - Slow motion (0.5x)
viewmode unlit    - View without lighting
```

### Useful Shortcuts
```
Ctrl+S           - Save current asset
Ctrl+Shift+S     - Save all
F5               - Play in editor
Shift+F1         - Mouse cursor in PIE
F8               - Eject from character
```

---

## Next Steps

1. ✅ Read this guide completely
2. ⬜ Install Unreal Engine 5
3. ⬜ Create project with settings above
4. ⬜ Set up folder structure
5. ⬜ Create basic character movement
6. ⬜ Follow Implementation Order
7. ⬜ Reference Blueprint docs as needed
8. ⬜ Test frequently!

---

*Take it step by step. Every AAA game started as a gray box. You've got this!*

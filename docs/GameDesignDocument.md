# 🎮 Verdant Heart - Game Design Document

**Version**: 1.0  
**Last Updated**: January 2026  
**Target Platform**: PC (potential console port)  
**Engine**: Unreal Engine 5.3+  
**Genre**: Third-Person Action-Adventure  
**Target Duration**: 15-30 minutes  

---

## 📋 Table of Contents

1. [Executive Summary](#executive-summary)
2. [Core Concept](#core-concept)
3. [Player Character](#player-character)
4. [Core Mechanics](#core-mechanics)
5. [Combat System](#combat-system)
6. [Puzzle Design](#puzzle-design)
7. [Traversal & Parkour](#traversal--parkour)
8. [Exploration & Secrets](#exploration--secrets)
9. [Progression Systems](#progression-systems)
10. [UI/UX Design](#uiux-design)
11. [Camera System](#camera-system)
12. [Audio Design](#audio-design)
13. [Accessibility](#accessibility)

---

## Executive Summary

**Verdant Heart** is a third-person action-adventure game set in an ancient mystical forest. Players take on the role of Kira Ashwood, an archaeologist who discovers a hidden realm where nature and ancient magic intertwine. The forest is dying, corrupted by a mysterious force, and only by reaching its Heart can the player restore balance.

### Key Selling Points
- **Atmospheric Exploration**: A beautiful, mysterious forest begging to be explored
- **Fluid Traversal**: Satisfying climbing, jumping, and parkour
- **Clever Puzzles**: Environmental puzzles that reward observation
- **Tight Combat**: Impactful encounters against corrupted creatures
- **Rich Lore**: A story told through environment, artifacts, and discoveries

### Inspirations
| Game | What We're Taking |
|------|-------------------|
| **Tomb Raider (2013+)** | Traversal feel, environmental puzzles, adventure tone |
| **Uncharted** | Cinematic moments, character personality, set pieces |
| **God of War (2018)** | Combat weight, camera work, environmental storytelling |
| **Ori and the Blind Forest** | Mystical forest atmosphere, emotional connection to nature |
| **Horizon Zero Dawn** | Lush environments, discovery-driven exploration |

---

## Core Concept

### The World
The **Verdant Realm** is an ancient forest that exists in a pocket dimension, hidden from the modern world. Once protected by the **Sylvan Guardians**, an ancient civilization that lived in harmony with the forest's magic, it now lies abandoned and corrupted.

### The Conflict
A creeping **Blight** has infected the forest, corrupting its creatures and withering its magic. The source of this corruption lies at the Heart of the Forest, where the ancient Guardians' greatest secret is hidden.

### The Journey
The player progresses through three distinct areas:

| Area | Focus | Duration |
|------|-------|----------|
| **The Sacred Grove** | Tutorial, exploration, light puzzles | 5-7 min |
| **The Ancient Ruins** | Combat, complex puzzles, parkour | 8-12 min |
| **The Heart of the Forest** | Climax, all mechanics combined | 5-8 min |

---

## Player Character

### Kira Ashwood

**Role**: Protagonist (playable character)  
**Age**: 32  
**Profession**: Archaeologist specializing in lost civilizations  
**Personality**: Curious, determined, witty in tense situations  

#### Visual Design
- Practical adventure attire (cargo pants, hiking boots, fitted jacket)
- Utility belt with tools
- Hair tied back practically
- Visible wear and tear as game progresses

#### Abilities (All available from start)
| Ability | Description | Button (Controller) |
|---------|-------------|---------------------|
| **Sprint** | Faster movement, limited duration | L3 (hold) |
| **Jump** | Standard jump | A/X |
| **Climb** | Grab ledges, climb surfaces | Automatic on contact |
| **Roll/Dodge** | Evasive maneuver, i-frames | B/Circle |
| **Interact** | Examine objects, pull levers | Y/Triangle |
| **Light Attack** | Quick staff strike | X/Square |
| **Heavy Attack** | Powerful charged attack | RT/R2 |
| **Focus Mode** | Highlights interactables | LB/L1 (hold) |

---

## Core Mechanics

### Movement Philosophy
Movement should feel **grounded but fluid**. Kira is athletic and capable, but human. No supernatural abilities—just peak human performance.

#### Basic Movement Stats
```
Walk Speed: 300 units/sec
Run Speed: 600 units/sec  
Sprint Speed: 850 units/sec
Jump Height: 180 units
Jump Distance: 400 units (running)
```

### Interaction System

#### Focus Mode (Detective Vision)
When held, **Focus Mode** subtly highlights:
- Climbable surfaces (faint golden shimmer)
- Interactable objects (gentle pulse)
- Collectibles (soft glow)
- Enemy weak points (during combat)

**Design Note**: Keep this subtle—we want players to explore naturally, not play "follow the highlights."

### State Machine Overview

```
                    ┌──────────────┐
                    │    IDLE      │
                    └──────┬───────┘
                           │
          ┌────────────────┼────────────────┐
          ▼                ▼                ▼
    ┌──────────┐    ┌──────────┐    ┌──────────┐
    │   MOVE   │    │  COMBAT  │    │  CLIMB   │
    └────┬─────┘    └────┬─────┘    └────┬─────┘
         │               │               │
         ▼               ▼               ▼
    ┌──────────┐    ┌──────────┐    ┌──────────┐
    │  SPRINT  │    │  DODGE   │    │   JUMP   │
    └──────────┘    └──────────┘    └──────────┘
```

---

## Combat System

### Philosophy
Combat is **supplementary, not central**. Encounters should feel dangerous and meaningful, not repetitive. Quality over quantity—fewer, better-designed fights.

### Combat Stats

#### Player Stats
```
Health: 100 HP
Stamina: 100 (regenerates when not attacking/sprinting)
I-Frames during dodge: 0.3 seconds
Stagger resistance: Medium
```

#### Weapon: Ancient Staff
Kira discovers an ancient Guardian staff early in the game. It serves as both tool and weapon.

| Attack | Damage | Stamina Cost | Speed |
|--------|--------|--------------|-------|
| Light Attack | 15 HP | 10 | Fast |
| Light Combo (3x) | 15+15+20 HP | 30 | Fast |
| Heavy Attack | 35 HP | 25 | Slow |
| Charged Heavy | 50 HP | 40 | Very Slow |
| Dodge Attack | 20 HP | 15 | Medium |

### Enemy Types

#### 1. Blighted Wolves (Common)
**Behavior**: Pack hunters, flanking tactics  
**Health**: 40 HP  
**Damage**: 15 HP per bite  
**Speed**: Fast  
**Weakness**: Vulnerable after lunge attack  

```
Attack Pattern:
1. Circle player (2-3 seconds)
2. One wolf lunges (telegraph: growl + crouch)
3. 1-second recovery window (PUNISH HERE)
4. Others attack if player misses opportunity
```

#### 2. Corrupted Treant (Mini-boss)
**Behavior**: Slow but powerful, area denial  
**Health**: 150 HP  
**Damage**: 30 HP (slam), 20 HP (swipe)  
**Speed**: Slow  
**Weakness**: Glowing core exposed after slam attack  

```
Attack Pattern:
1. Slow approach
2. Ground Slam (3-second telegraph, 1.5s recovery)
   └─ Exposes glowing core - ATTACK NOW
3. Wide Swipe (1-second telegraph)
4. Root Eruption (area denial, creates obstacles)
```

#### 3. The Blighted Heart (Final Boss)
**See**: `docs/LevelDesign/Area3-HeartOfForest.md`

### Combat Encounter Design

#### Encounter Pacing
```
Area 1 (Sacred Grove):     1 tutorial encounter (2-3 wolves)
Area 2 (Ancient Ruins):    3 encounters + 1 mini-boss
Area 3 (Heart of Forest):  1 gauntlet + Final Boss
```

#### Arena Design Principles
- Always provide cover/pillars for breathing room
- Multiple elevations when possible
- Environmental hazards (optional player advantage)
- Clear boundaries (invisible walls feel bad—use natural barriers)

---

## Puzzle Design

### Puzzle Philosophy
Puzzles should:
1. **Reward observation** - The solution is visible if you look
2. **Feel logical** - "Of course!" not "How was I supposed to know?"
3. **Use the environment** - No abstract puzzle rooms
4. **Teach then test** - Introduce mechanic simply, then add complexity

### Puzzle Types

#### 1. Beam Reflection Puzzles
**Mechanic**: Redirect light beams using ancient mirrors  
**Complexity Progression**:
- Simple: One mirror, direct path
- Medium: Multiple mirrors, obstacles
- Complex: Timed elements, moving parts

```
Example Layout (Area 2):

    [LIGHT SOURCE]
          │
          ▼
    ┌─────────┐         
    │ MIRROR 1│ ←── Player rotates
    └────┬────┘
         │ (beam reflects)
         ▼
    ┌─────────┐
    │ MIRROR 2│ ←── Player rotates  
    └────┬────┘
         │
         ▼
    [RECEIVER/DOOR]
```

#### 2. Weighted Pressure Plates
**Mechanic**: Place objects or stand on plates to open paths  
**Variations**:
- Single plate: Player weight
- Multiple plates: Find objects to place
- Sequence plates: Correct order required

#### 3. Ancient Symbol Matching
**Mechanic**: Align symbols found in environment to unlock doors  
**Design**: Symbols are scattered in the area—exploration required

#### 4. Water Flow Puzzles (Area 2)
**Mechanic**: Redirect water channels to power mechanisms  
**Elements**: Sluice gates, rotating channels, water wheels

#### 5. Growth/Decay Mechanic (Area 3)
**Mechanic**: Staff can temporarily restore or wither Blighted plants  
**Uses**: Create platforms, clear paths, reveal hidden areas

### Puzzle Difficulty Curve

```
Puzzle Complexity Over Time:

  Complex │                          ╭────
          │                    ╭─────╯
          │              ╭─────╯
  Medium  │        ╭─────╯
          │  ╭─────╯
          │──╯
  Simple  └──────────────────────────────────
           Area 1    Area 2       Area 3
```

---

## Traversal & Parkour

### Climbable Surfaces
Not everything is climbable—specific surfaces are designed for climbing:
- Rough stone walls (visual: protruding rocks, cracks)
- Ancient Guardian structures (visual: carved handholds)
- Thick vines and roots
- Wooden scaffolding/beams

### Traversal Actions

#### Ledge Grab
- Auto-grab when jumping toward climbable ledge
- Shimmy left/right along ledges
- Pull up or drop down

#### Wall Run (Limited)
- Short horizontal wall runs between platforms
- Maximum 2 seconds, then fall

#### Rope Swing
- Specific rope/vine swing points
- Momentum-based (timing matters)

#### Balance Beam
- Narrow surfaces require careful walking
- Push to either side makes Kira wobble/recover

### Traversal Flow Example

```
[PLATFORM A]
     │
     └──► Jump to ──► [LEDGE] 
                         │
                         └──► Shimmy ──► [CORNER]
                                            │
                                            └──► Pull Up ──► [PLATFORM B]
                                                                 │
                                                                 └──► Wall Run ──► [ROPE]
                                                                                     │
                                                                                     └──► Swing ──► [PLATFORM C]
```

---

## Exploration & Secrets

### Collectible Types

#### 1. Lore Stones (12 total)
**Purpose**: Tell the story of the Sylvan Guardians  
**Location**: Hidden throughout all areas  
**Reward**: Story context, achievement  

#### 2. Spirit Essence (25 total)
**Purpose**: Floating motes of light  
**Location**: Some obvious, some require exploration  
**Reward**: Health upgrade every 5 collected  

#### 3. Guardian Relics (3 total)
**Purpose**: Major collectibles, one per area  
**Location**: Requires puzzle-solving or optional challenges  
**Reward**: Unlocks bonus content (concept art, lore entries)  

### Secret Areas
Each area has at least one hidden zone:
- **Area 1**: Hidden grove behind waterfall
- **Area 2**: Collapsed lower level with treasure
- **Area 3**: Memorial chamber with final lore piece

### Exploration Rewards

| Exploration Level | Reward |
|-------------------|--------|
| 25% collectibles | Health upgrade |
| 50% collectibles | Stamina upgrade |
| 75% collectibles | Staff damage upgrade |
| 100% collectibles | Alternate ending scene |

---

## Progression Systems

### No XP/Leveling
This is a short demo—avoid progression bloat. All abilities available from start.

### Health Upgrades
- Base: 100 HP
- +20 HP per Spirit Essence milestone (5, 10, 15, 20, 25)
- Maximum: 200 HP

### Checkpoint System
- Auto-save at area transitions
- Checkpoints before major encounters
- Checkpoints after puzzle completion
- Death returns to last checkpoint (no progress loss)

---

## UI/UX Design

### HUD Philosophy
**Minimal and diegetic where possible.**

### HUD Elements

```
┌────────────────────────────────────────────────────────┐
│ [Health Bar]                              [Compass]    │
│                                                        │
│                                                        │
│                                                        │
│                                                        │
│                                                        │
│                                                        │
│                                                        │
│                      [GAMEPLAY AREA]                   │
│                                                        │
│                                                        │
│                                                        │
│                                                        │
│                                                        │
│                                                        │
│                                           [Interact]   │
│ [Stamina Bar]                             [Prompt]     │
└────────────────────────────────────────────────────────┘
```

### UI Fade Rules
- Health bar: Fades after 3 seconds of no damage
- Stamina bar: Fades after 3 seconds of no stamina use
- Interaction prompts: Appear within range, fade on exit

### Menus

#### Pause Menu
- Resume
- Collectibles (view found items)
- Controls
- Settings (audio, display)
- Quit to Menu

#### Settings
- Master Volume
- Music Volume
- SFX Volume
- Subtitles (On/Off/Speaker Names)
- Camera Sensitivity
- Invert Y-Axis

---

## Camera System

### Camera Behavior

#### Default Following Camera
```
Distance from player: 350 units
Height offset: 80 units
FOV: 75°
Look-ahead: Subtle (camera shifts toward movement direction)
```

#### Combat Camera
```
Distance: 400 units (pulled back slightly)
Height offset: 100 units
Auto-target: Soft lock to nearest enemy
```

#### Cinematic Moments
- Pre-placed camera positions for vistas
- Smooth transitions (no hard cuts)
- Player retains movement control

### Camera Collision
- Camera pushes forward when hitting walls
- Transparent fade for objects between camera and player
- Never clip through geometry

---

## Audio Design

### Music Approach

| Situation | Music Style |
|-----------|-------------|
| Exploration | Ambient, mysterious, soft orchestra |
| Discovery | Swelling strings, wonder |
| Combat | Percussion-driven, tense |
| Puzzle solving | Minimal, thoughtful |
| Boss fight | Epic, full orchestra |
| Victory | Triumphant, release of tension |

### Sound Effects Priority

1. **Player Feedback**: Footsteps, attacks, damage taken
2. **Environmental**: Water, wind, rustling leaves
3. **UI**: Menu navigation, item pickup
4. **Creatures**: Enemy vocalizations, attack sounds
5. **Ambient**: Distant wildlife, cave echoes

### Voice
- **Kira**: Internal monologue for observations, hints
- **Environmental**: Whispers from Lore Stones
- Keep dialogue minimal—show don't tell

---

## Accessibility

### Visual Accessibility
- Colorblind modes (Deuteranopia, Protanopia, Tritanopia)
- High contrast option for interactables
- Scalable UI
- Subtitle options (size, background, speaker colors)

### Motor Accessibility
- Fully remappable controls
- Toggle vs hold options for sprint/focus
- Adjustable aim sensitivity
- Auto-climb option (removes timing requirements)

### Cognitive Accessibility
- Pause during cutscenes
- Objective reminder system
- Adjustable puzzle hints (subtle → obvious)
- Combat difficulty options

---

## Appendix: Quick Reference

### Controls (Default Controller)
| Action | Button |
|--------|--------|
| Move | Left Stick |
| Camera | Right Stick |
| Jump | A / X |
| Dodge | B / Circle |
| Interact | Y / Triangle |
| Light Attack | X / Square |
| Heavy Attack | RT / R2 |
| Sprint | L3 (hold) |
| Focus Mode | LB / L1 (hold) |
| Pause | Start |

### Key Metrics
- Target framerate: 60 FPS
- Demo duration: 15-30 minutes
- Collectibles: 40 total
- Enemy types: 3
- Puzzle types: 5
- Areas: 3

---

*Document maintained as source of truth for game design decisions.*

# 🗺️ Level Design Overview

**Document Version**: 1.0  
**Game**: Verdant Heart  

---

## Design Philosophy

### Guiding Principles

1. **Readability**: Players should always understand where they can go
2. **Reward Curiosity**: Every detour should feel worthwhile
3. **Visual Storytelling**: Environments tell the story without words
4. **Pacing Control**: Alternate tension and release deliberately
5. **Player Agency**: Multiple paths where possible, even if they converge

### The "Weenie" Approach (Disney Imagineering)
Each area has a visible landmark that draws players forward:
- **Sacred Grove**: The ancient tree visible from the entrance
- **Ancient Ruins**: The central spire rising above the structures
- **Heart of the Forest**: The glowing Heart visible through the trees

---

## Level Flow Overview

```
                           ┌─────────────────────────────────────────┐
                           │           GAME START                     │
                           │     Mountain entrance discovery          │
                           └────────────────┬────────────────────────┘
                                            │
                                            ▼
                    ┌───────────────────────────────────────────────┐
                    │              AREA 1: SACRED GROVE              │
                    │   Duration: 5-7 minutes │ Focus: Tutorial     │
                    ├───────────────────────────────────────────────┤
                    │  • Movement tutorial (natural obstacles)       │
                    │  • First combat encounter (2-3 wolves)         │
                    │  • First puzzle (simple beam puzzle)           │
                    │  • Acquire Guardian Staff                      │
                    │  • 4 Lore Stones, 8 Spirit Essence             │
                    │  • 1 Guardian Relic (optional)                 │
                    │  • Secret Area: Hidden Grove behind waterfall  │
                    └────────────────────┬──────────────────────────┘
                                         │
                                         ▼
                    ┌───────────────────────────────────────────────┐
                    │             AREA 2: ANCIENT RUINS              │
                    │   Duration: 8-12 minutes │ Focus: Core Play    │
                    ├───────────────────────────────────────────────┤
                    │  • Complex puzzles (water flow, symbols)       │
                    │  • Multiple combat encounters                  │
                    │  • Parkour sequences                           │
                    │  • Mini-boss: Corrupted Treant                 │
                    │  • Major story revelations                     │
                    │  • 5 Lore Stones, 12 Spirit Essence            │
                    │  • 1 Guardian Relic (optional)                 │
                    │  • Secret Area: Collapsed lower level          │
                    └────────────────────┬──────────────────────────┘
                                         │
                                         ▼
                    ┌───────────────────────────────────────────────┐
                    │           AREA 3: HEART OF THE FOREST          │
                    │   Duration: 5-8 minutes │ Focus: Climax        │
                    ├───────────────────────────────────────────────┤
                    │  • Mixed mechanics gauntlet                    │
                    │  • Final boss: The Blighted Heart              │
                    │  • Grandmother's final message                 │
                    │  • Resolution and ending                       │
                    │  • 3 Lore Stones, 5 Spirit Essence             │
                    │  • 1 Guardian Relic (optional)                 │
                    │  • Secret Area: Memorial chamber               │
                    └────────────────────┬──────────────────────────┘
                                         │
                                         ▼
                           ┌─────────────────────────────────────────┐
                           │              GAME END                    │
                           │       Ending cinematic plays             │
                           └─────────────────────────────────────────┘
```

---

## Environment Design Guidelines

### Visual Language

| Element | Meaning |
|---------|---------|
| **Golden shimmer** | Climbable/interactive surface |
| **Blue glow** | Collectible nearby |
| **Purple/black tendrils** | Corruption/danger zone |
| **Soft white light** | Safe area/checkpoint |
| **Green pulse** | Health restoration |

### Color Palette by Area

**Sacred Grove**
- Dominant: Deep greens, golden sunlight
- Accent: Corruption purple at edges
- Mood: Beautiful but melancholic

**Ancient Ruins**
- Dominant: Weathered stone grays, moss greens
- Accent: Guardian gold in architecture
- Mood: Mysterious, historical weight

**Heart of the Forest**
- Dominant: Shifting between pure white and corruption black
- Accent: Intense gold and deep purple
- Mood: Surreal, climactic

### Lighting Approach

```
Sacred Grove:     Dappled sunlight through canopy
                  God rays in key vista moments
                  Corruption areas are darker, desaturated

Ancient Ruins:    Interior: Torch/bioluminescent lighting
                  Exterior: Overcast, moody
                  Puzzle elements: Distinct light sources

Heart of Forest:  Dynamic lighting shifts
                  Boss arena: Dramatic contrast
                  Ending: Golden hour restoration
```

---

## Collectible Distribution

### Spirit Essence (25 Total)

| Area | Count | Placement Philosophy |
|------|-------|---------------------|
| Sacred Grove | 8 | Most visible, teaches player to look |
| Ancient Ruins | 12 | Mix of obvious and hidden |
| Heart of Forest | 5 | All require some effort |

### Lore Stones (12 Total)

| Area | Count | Placement |
|------|-------|-----------|
| Sacred Grove | 4 | Near main path, introduces lore system |
| Ancient Ruins | 5 | Hidden in explorable spaces, major revelations |
| Heart of Forest | 3 | Final revelations, emotional climax |

### Guardian Relics (3 Total)

| Area | Location | Challenge Required |
|------|----------|-------------------|
| Sacred Grove | Behind waterfall | Find secret entrance |
| Ancient Ruins | Lower level | Complete optional puzzle |
| Heart of Forest | Memorial chamber | Defeat optional challenge |

---

## Traversal Landmarks

### Sacred Grove
- Giant fallen tree (bridge)
- Climbable cliff face
- Stepping stones across stream
- Rope swing over gap

### Ancient Ruins
- Crumbling towers (vertical traversal)
- Collapsed bridge (balance beam)
- Interior wall-running sections
- Elevator platforms (puzzle-activated)

### Heart of the Forest
- Floating platforms (magic-sustained)
- Root bridges (living traversal)
- Final climb to Heart
- Corruption walls (time-limited passages)

---

## Enemy Placement Philosophy

### Encounter Pacing

```
Intensity over time:

  HIGH  │                        ╱╲
        │                       ╱  ╲
        │            ╱╲        ╱    ╲___BOSS
  MED   │     ╱╲    ╱  ╲      ╱
        │    ╱  ╲  ╱    ╲    ╱
        │   ╱    ╲╱      ╲  ╱
  LOW   │__╱              ╲╱
        └────────────────────────────────────
          Tutorial  Mid-game    Pre-boss  Boss
```

### Combat Arena Checklist

- [ ] Clear boundaries (natural, not invisible walls)
- [ ] At least one piece of cover
- [ ] Escape routes visible but blocked until combat ends
- [ ] Environmental hazard (optional player advantage)
- [ ] Post-combat reward (item, path forward, lore)

---

## Puzzle Placement

### Progressive Complexity

| Puzzle | Area | Type | Complexity | Teaching |
|--------|------|------|------------|----------|
| Beam 1 | Grove | Light reflection | Simple | Introduces mechanic |
| Plate 1 | Grove | Pressure plate | Simple | Stand and open |
| Beam 2 | Ruins | Light reflection | Medium | Multiple mirrors |
| Water 1 | Ruins | Flow direction | Medium | Introduces mechanic |
| Symbol | Ruins | Pattern match | Medium | Exploration required |
| Water 2 | Ruins | Flow + timing | Complex | All elements |
| Growth | Heart | Staff ability | Complex | Time-limited |
| Final | Heart | Combined | Complex | Everything learned |

---

## Checkpoint Placement

### Auto-Save Triggers

1. Entering new area
2. After completing any puzzle
3. Before any combat encounter
4. After any combat encounter
5. After acquiring key item
6. After major story beat

### Visual Checkpoint Indicators
- Soft white light column
- Guardian symbol on ground
- Subtle sound cue (chime)

---

## Metrics & Scale Reference

### Player Character
- Height: 180 units
- Width: 50 units
- Jump height: 180 units
- Jump distance: 400 units

### Space Design
```
Corridor (minimum):     200 units wide
Combat arena (small):   800 x 800 units
Combat arena (large):   1500 x 1500 units
Puzzle room:            Variable (500-1200 based on puzzle)
Vista overlook:         Platform 100 units, view distance 5000+
```

### Ledge Heights
```
Step up (auto):         < 40 units
Vault (automatic):      40-100 units
Climb (grab required):  100-200 units
Jump required:          > 200 units
```

---

## Area Summary Table

| Aspect | Sacred Grove | Ancient Ruins | Heart of Forest |
|--------|--------------|---------------|-----------------|
| **Duration** | 5-7 min | 8-12 min | 5-8 min |
| **Combat** | 1 encounter | 4 encounters + boss | 1 gauntlet + boss |
| **Puzzles** | 2 simple | 4 medium-complex | 2 complex |
| **Traversal** | Basic intro | Full range | Mixed + unique |
| **Tone** | Wonder + unease | Discovery + danger | Surreal + climactic |
| **Music** | Ambient/curious | Mysterious/tense | Epic/emotional |

---

## See Also

- [Area 1: Sacred Grove](Area1-SacredGrove.md) - Detailed level design
- [Area 2: Ancient Ruins](Area2-AncientRuins.md) - Detailed level design
- [Area 3: Heart of the Forest](Area3-HeartOfForest.md) - Detailed level design

---

*Level design documents are living documents—update as development reveals what works.*

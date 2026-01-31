# 🎨 Asset Requirements: 3D Models

**Document Version**: 1.0  
**Target Platform**: PC (RTX capable)  
**Art Style**: Stylized Realism  

---

## Art Direction Summary

**Visual Style**: Stylized realism with painterly textures. Think Horizon Zero Dawn meets Ori and the Blind Forest—grounded but with magical flourishes.

**Color Philosophy**:
- Healthy forest: Rich greens, warm golds, soft blues
- Corrupted areas: Deep purples, sickly blacks, desaturated colors
- Guardian artifacts: Warm gold with soft glow

---

## Character Models

### Kira Ashwood (Player Character)

| Specification | Value |
|---------------|-------|
| Polycount | 30,000-50,000 tris |
| Skeleton | UE5 Mannequin compatible |
| Materials | 3 (body, gear, hair) |
| Texture Resolution | 4K diffuse, normal, ORM |

**Required States**:
- Default appearance
- Battle damage variant (late game)

**Outfit Details**:
- Fitted adventure jacket (earth tones)
- Cargo pants with knee pads
- Hiking boots
- Utility belt with pouches
- Hair tied back (ponytail)
- Grandmother's necklace (always visible)

---

### Enemies

#### Blighted Wolf

| Specification | Value |
|---------------|-------|
| Polycount | 8,000-12,000 tris |
| Skeleton | Quadruped rig |
| Materials | 2 (body, corruption effects) |
| Texture Resolution | 2K |

**Visual Notes**:
- Base wolf form (recognizable)
- Corruption tendrils across body
- Glowing purple eyes
- Shadowy particles emanating
- Exposed bone/corruption at joints

**Variants Needed**:
1. Standard Wolf
2. Alpha Wolf (larger, more corruption)

---

#### Corrupted Treant (Mini-Boss)

| Specification | Value |
|---------------|-------|
| Polycount | 25,000-35,000 tris |
| Skeleton | Custom (humanoid tree) |
| Materials | 3 (bark, leaves, corruption/core) |
| Texture Resolution | 4K |

**Visual Notes**:
- Ancient tree given humanoid form
- Moss and vines covering body
- Visible corruption spreading from base
- Glowing core in chest (weak point)
- Branch "arms" with claw-like ends
- Face suggested in bark patterns

---

#### The Blighted Heart (Final Boss)

| Specification | Value |
|---------------|-------|
| Polycount | 50,000+ tris (environment piece) |
| Type | Static mesh with animated elements |
| Materials | 4 (trunk, roots, corruption, light core) |
| Texture Resolution | 4K |

**Visual Notes**:
- Massive ancient tree at center
- Roots spreading across arena
- Corruption wrapped around trunk
- Pulsing light at core
- Shifting between corrupted/purified states

---

## Props & Interactables

### Guardian Staff (Player Weapon)

| Specification | Value |
|---------------|-------|
| Polycount | 2,000-3,000 tris |
| Materials | 2 (wood, metal/gem) |
| Texture Resolution | 2K |

**Visual Notes**:
- Elegant carved wood
- Gold metal fittings
- Gem at head (glows when using abilities)
- Guardian symbols etched along shaft

---

### Collectibles

#### Spirit Essence
| Spec | Value |
|------|-------|
| Type | Particle system + simple mesh |
| Polycount | 100 tris |
| Material | Emissive, translucent |

**Visual**: Floating mote of golden light, gentle bob animation

#### Lore Stone
| Spec | Value |
|------|-------|
| Polycount | 500-1,000 tris |
| Materials | 1 (stone with emissive symbols) |

**Visual**: Standing stone with carved Guardian symbols, glows when active

#### Guardian Relic
| Spec | Value |
|------|-------|
| Polycount | 1,500 tris |
| Materials | 2 (base, emissive) |

**Visual**: Ornate artifact on pedestal, distinct per relic

---

### Puzzle Elements

#### Light Beam Mirror
| Spec | Value |
|------|-------|
| Polycount | 1,500 tris |
| Materials | 2 (frame, reflective surface) |

**Visual**: Ancient brass frame, mystical mirror surface

#### Light Source Crystal
| Spec | Value |
|------|-------|
| Polycount | 800 tris |
| Materials | 1 (emissive crystal) |

**Visual**: Large crystal emitting beam of light

#### Pressure Plate
| Spec | Value |
|------|-------|
| Polycount | 500 tris |
| Materials | 1 (stone with symbols) |

**Visual**: Circular stone plate with Guardian markings

#### Pushable Block
| Spec | Value |
|------|-------|
| Polycount | 200 tris |
| Materials | 1 (stone) |

**Visual**: Weathered stone cube, clearly moveable

#### Sluice Gate / Water Wheel
| Spec | Value |
|------|-------|
| Polycount | 2,000 tris each |
| Materials | 2 (wood, metal) |

**Visual**: Ancient but functional water mechanisms

---

## Environment Assets

### Sacred Grove (Area 1)

**Trees & Vegetation**:
| Asset | Polycount | Quantity Needed |
|-------|-----------|-----------------|
| Giant Ancient Tree | 15,000 | 1 (centerpiece) |
| Large Forest Tree | 5,000 | 10-15 variants |
| Medium Tree | 2,500 | 5-8 variants |
| Bush/Shrub | 500 | 8-10 variants |
| Fern | 300 | 5 variants |
| Grass clump | 100 | 3 variants |
| Flowers | 200 | 5 variants |
| Fallen log | 1,500 | 3 variants |
| Rock (large) | 1,000 | 5 variants |
| Rock (small) | 300 | 5 variants |

**Structures**:
| Asset | Polycount |
|-------|-----------|
| Guardian Shrine | 3,000 |
| Bridge (wooden) | 2,000 |
| Waterfall rocks | 2,500 |
| Stream bed | 1,500 |

**Corruption Variants**:
- Corrupted versions of key vegetation
- Black/purple material variants
- Withered versions

---

### Ancient Ruins (Area 2)

**Architectural Elements**:
| Asset | Polycount | Quantity |
|-------|-----------|----------|
| Column (intact) | 2,000 | 10+ |
| Column (broken) | 1,500 | 5+ |
| Wall section | 3,000 | Modular |
| Archway | 4,000 | 5 variants |
| Door frame | 2,500 | 3 variants |
| Stairs | 2,000 | Modular |
| Floor tiles | 500 | Modular |
| Ceiling beams | 1,000 | Modular |
| Central Spire | 15,000 | 1 |

**Guardian Home Props**:
| Asset | Polycount |
|-------|-----------|
| Table | 800 |
| Chair | 400 |
| Bed | 1,000 |
| Bookshelf | 1,200 |
| Books/scrolls | 100 each |
| Pottery | 300 |
| Cooking pot | 400 |
| Children's toys | 200 each |
| Personal shrine | 800 |

**Decay/Overgrowth**:
- Vines growing on structures
- Cracked/broken variants
- Moss coverage materials

---

### Heart of the Forest (Area 3)

**Unique Elements**:
| Asset | Polycount |
|-------|-----------|
| Floating platform | 1,500 |
| Root bridge | 3,000 |
| Memory crystal | 500 |
| Corruption wall | 2,000 |
| Memorial stone | 1,000 |
| The Heart (boss arena) | See Boss section |

**Reality Distortion Props**:
- Objects frozen mid-motion
- Split/duplicated geometry
- Ethereal variants of existing assets

---

## Material Guidelines

### Base Materials Needed

1. **Bark/Wood** - Multiple variants (healthy, corrupted, ancient)
2. **Stone** - Guardian carved, natural rock, ruins
3. **Metal** - Guardian gold, aged bronze
4. **Foliage** - Leaves, grass, moss (healthy + corrupted)
5. **Water** - Stream, waterfall, puddles
6. **Crystal** - Light puzzle elements
7. **Corruption** - Black tendrils, purple glow
8. **Fabric** - For character clothing

### Material Features
- All materials should support:
  - Wet variant (rain/water areas)
  - Corruption blend (0-1 parameter)
  - Distance fade for foliage

---

## LOD Requirements

| Distance | LOD Level | Polycount Reduction |
|----------|-----------|---------------------|
| 0-10m | LOD0 | 100% |
| 10-30m | LOD1 | 50% |
| 30-60m | LOD2 | 25% |
| 60m+ | LOD3 | 10% |

---

## Asset Sources

### Recommended Approaches

1. **Unreal Marketplace**
   - Forest/nature packs for base vegetation
   - Modular ruins kits
   - Character base meshes for customization

2. **Quixel Megascans** (Free with UE5)
   - Rocks and terrain
   - Foliage
   - Surface materials

3. **Custom Creation**
   - Kira character (unique)
   - Enemies (unique designs)
   - Guardian-specific architecture
   - Key story props

4. **Mixamo** (Free)
   - Base animations for character
   - Humanoid enemy animations

---

## Naming Conventions

```
SM_[Category]_[Name]_[Variant]
SK_[Category]_[Name]
M_[Category]_[Name]
MI_[Category]_[Name]_[Instance]

Examples:
SM_Env_Tree_Large_01
SM_Prop_Mirror_Puzzle
SK_Char_Kira
SK_Enemy_Wolf_Alpha
M_Nature_Bark_Healthy
MI_Nature_Bark_Corrupted
```

---

## Priority List

### Must Have (MVP)
- [ ] Kira character model
- [ ] Blighted Wolf
- [ ] Guardian Staff
- [ ] Basic forest vegetation (can use marketplace)
- [ ] Puzzle elements (mirrors, plates, etc.)
- [ ] Collectibles
- [ ] Basic ruins modular kit

### Should Have
- [ ] Corrupted Treant
- [ ] Guardian home props
- [ ] Environmental storytelling props
- [ ] Corruption variants

### Nice to Have
- [ ] Blighted Heart boss
- [ ] Area 3 unique assets
- [ ] Additional vegetation variety
- [ ] Extra prop details

---

*Art assets should support the narrative. Every prop should feel like it belongs in this world.*

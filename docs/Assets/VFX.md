# ✨ Asset Requirements: Visual Effects

**Document Version**: 1.0  
**VFX System**: Niagara (UE5)  
**Style**: Stylized, Magical, Nature-Inspired  

---

## VFX Direction

### Overall Style
Effects should feel **organic and magical**, not technological. Think particle-based nature magic—light, leaves, water, energy—rather than lasers and sci-fi elements.

### Color Palette
| Category | Primary | Secondary | Accent |
|----------|---------|-----------|--------|
| **Positive/Life** | Warm gold | Soft green | White sparkles |
| **Corruption** | Deep purple | Sickly black | Dark particles |
| **Neutral/Magic** | Soft blue | Silver | Gentle glow |
| **Damage** | Orange-red | Dark red | Impact flash |

---

## Player VFX

### Movement Effects

#### Footstep Dust
| Property | Value |
|----------|-------|
| Trigger | On footstep |
| Particles | 5-10 small dust |
| Lifetime | 0.5 sec |
| Color | Surface dependent |

**Variants**: Dirt, stone, grass (subtle), water splash

#### Sprint Trail
| Property | Value |
|----------|-------|
| Trigger | While sprinting |
| Type | Subtle motion blur |
| Opacity | 20% |

#### Jump/Land Impact
| Property | Value |
|----------|-------|
| Trigger | On land |
| Particles | 8-15 |
| Scale | Based on fall height |
| Spread | Radial |

---

### Combat Effects

#### Light Attack Swing
| Property | Value |
|----------|-------|
| Type | Weapon trail |
| Color | Warm gold |
| Opacity | 60% → 0% |
| Duration | 0.15 sec |

#### Heavy Attack Swing
| Property | Value |
|----------|-------|
| Type | Weapon trail + particles |
| Color | Bright gold |
| Particles | Energy sparks |
| Duration | 0.3 sec |

#### Charged Heavy Buildup
| Property | Value |
|----------|-------|
| Type | Energy gathering |
| Particles | Swirling toward staff |
| Color | Gold → Bright white |
| Scale | Grows over charge |

#### Charged Heavy Release
| Property | Value |
|----------|-------|
| Type | Burst + ground crack |
| Particles | 50+ |
| Spread | AoE indicator |
| Screen shake | Yes |

#### Hit Impact (On Enemy)
| Property | Value |
|----------|-------|
| Type | Burst at contact |
| Particles | 15-20 |
| Color | Gold + enemy corruption |
| Hitstop | 0.05 sec time freeze |

#### Dodge Roll Trail
| Property | Value |
|----------|-------|
| Type | Motion blur + dust |
| Opacity | Low |
| Duration | Dodge length |

#### I-Frame Visual
| Property | Value |
|----------|-------|
| Type | Brief ghost/afterimage |
| Opacity | 30% |
| Timing | During i-frames |

---

### Taking Damage

#### Hit Flash
| Property | Value |
|----------|-------|
| Type | Material flash |
| Color | Red-white |
| Duration | 0.1 sec |

#### Health Bar Flash
| Property | Value |
|----------|-------|
| Type | UI pulse |
| Color | Red |
| Scale | Slight grow-shrink |

#### Low Health Warning
| Property | Value |
|----------|-------|
| Type | Screen edge vignette |
| Color | Dark red |
| Opacity | Pulses with heartbeat |
| Trigger | Health < 25% |

#### Death Effect
| Property | Value |
|----------|-------|
| Type | Fade + particle scatter |
| Particles | Light motes leaving body |
| Color | Warm gold |

---

### Ability VFX

#### Focus Mode
| Property | Value |
|----------|-------|
| Type | Post-process + highlights |
| Screen | Slight desaturation |
| Highlighted objects | Soft gold glow |
| Particles | Subtle floating dust |

#### Growth Ability (Area 3)
| Property | Value |
|----------|-------|
| Type | Staff glow + beam |
| Color | Vibrant green + gold |
| Particles | Nature energy |
| Target | Plant growth effect |

#### Decay Ability (Area 3)
| Property | Value |
|----------|-------|
| Type | Staff glow + beam |
| Color | Purple + black |
| Particles | Corruption energy |
| Target | Plant withering effect |

---

## Enemy VFX

### Blighted Wolf

#### Ambient Corruption
| Property | Value |
|----------|-------|
| Type | Constant particle emission |
| Particles | Dark wisps |
| Color | Purple-black |
| Rate | 3-5 per second |

#### Eye Glow
| Property | Value |
|----------|-------|
| Type | Point light + glow |
| Color | Sickly purple |
| Intensity | Pulses slightly |

#### Attack Telegraph (Lunge)
| Property | Value |
|----------|-------|
| Type | Ground indicator |
| Shape | Line toward player |
| Color | Red warning |
| Duration | 0.5 sec telegraph |

#### Death Dissipation
| Property | Value |
|----------|-------|
| Type | Corruption leaving body |
| Particles | Dark wisps dispersing |
| Duration | 1 sec |
| Residue | Corruption pool fades |

---

### Corrupted Treant

#### Ambient Creaking
| Property | Value |
|----------|-------|
| Type | Wood particle dust |
| Rate | Occasional |
| Color | Brown dust |

#### Ground Slam Telegraph
| Property | Value |
|----------|-------|
| Type | Ground crack/glow |
| Shape | Circle AoE |
| Color | Red → Brighter |
| Duration | 3 sec buildup |

#### Ground Slam Impact
| Property | Value |
|----------|-------|
| Type | Debris + shockwave |
| Particles | 100+ (rocks, dust) |
| Screen shake | Large |
| Ground crack | Decal |

#### Core Exposed
| Property | Value |
|----------|-------|
| Type | Glow + particles |
| Color | Bright gold |
| Particles | Light motes |
| Duration | Vulnerability window |

#### Root Eruption
| Property | Value |
|----------|-------|
| Type | Ground burst |
| Particles | Dirt + root pieces |
| Trail | Lingering corruption |

#### Death/Purification
| Property | Value |
|----------|-------|
| Type | Corruption leaving |
| Transformation | Dark → Light |
| Particles | Gold light spreading |
| Duration | 3-4 sec |

---

### Blighted Heart (Boss)

#### Heartbeat Pulse
| Property | Value |
|----------|-------|
| Type | Energy wave |
| Spread | Outward from center |
| Color | Purple → Gold (shifting) |
| Rate | Rhythmic |

#### Root Attack
| Property | Value |
|----------|-------|
| Type | Ground eruption |
| Particles | Corruption + debris |
| Trail | Corruption residue |

#### Corruption Wave
| Property | Value |
|----------|-------|
| Type | Ground spread |
| Shape | Expanding circle |
| Color | Dark purple |
| Damage zone | Visual indicator |

#### Dark Pulse Charge
| Property | Value |
|----------|-------|
| Type | Energy gathering |
| Particles | Darkness converging |
| Scale | Grows dramatically |
| Duration | 3 sec |

#### Dark Pulse Release
| Property | Value |
|----------|-------|
| Type | Massive burst |
| Particles | 200+ |
| Screen flash | Dark |
| Screen shake | Extreme |

#### Phase Transition
| Property | Value |
|----------|-------|
| Type | State shift |
| Effect | Corruption surge |
| Color shift | Darker |
| Particles | Intensified |

#### Memory Assault
| Property | Value |
|----------|-------|
| Type | Screen distortion |
| Effect | Vision overlay |
| Particles | Memory fragments |
| Color | Desaturated + flashbacks |

#### Defeat/Purification
| Property | Value |
|----------|-------|
| Type | Corruption leaving |
| Duration | 10+ sec (dramatic) |
| Particles | Light overwhelming dark |
| Color | Dark → Pure gold/white |

---

## Environment VFX

### Sacred Grove

#### Ambient Particles
| Effect | Description |
|--------|-------------|
| Floating pollen | Golden motes, gentle drift |
| Fireflies | Night/dark areas |
| Leaf fall | Occasional, wind-driven |
| God rays | Through canopy |
| Water sparkle | On stream surface |

#### Waterfall
| Property | Value |
|----------|-------|
| Type | Niagara fluid |
| Particles | Mist at base |
| Color | Blue-white |
| Sound | Ambient loop |

---

### Ancient Ruins

#### Ambient Particles
| Effect | Description |
|--------|-------------|
| Dust motes | In light beams |
| Debris fall | Occasional small stones |
| Torch flicker | If using torches |
| Ghost echoes | Translucent figures |

#### Ghost Echo Effect
| Property | Value |
|----------|-------|
| Type | Translucent mesh |
| Opacity | 30-50% |
| Color | Blue-white |
| Effect | Slight glow, particles |
| Fade | In/out over 1-2 sec |

---

### Heart of the Forest

#### Reality Distortion
| Effect | Description |
|--------|-------------|
| Space warping | Visual distortion |
| Time fragments | Frozen particles |
| Color bleeding | Oversaturation spots |
| Flicker | Occasional visual glitch |

#### Corruption Ambient
| Effect | Description |
|--------|-------------|
| Dark particles | Heavy in corrupted areas |
| Ground fog | Purple mist |
| Tendril growth | Animated corruption |
| Energy pulse | Rhythmic glow |

#### Restoration (Post-Victory)
| Property | Value |
|----------|-------|
| Type | Purification spread |
| Particles | Light overwhelming dark |
| Duration | 30+ sec |
| Scale | Environment-wide |

---

## Puzzle VFX

### Beam Reflection

#### Light Beam
| Property | Value |
|----------|-------|
| Type | Niagara beam |
| Color | Warm gold |
| Width | 10-15 units |
| Particles | Floating along beam |

#### Mirror Reflection
| Property | Value |
|----------|-------|
| Effect | Bright flash on redirect |
| Duration | 0.1 sec |

#### Receiver Active
| Property | Value |
|----------|-------|
| Type | Glow + particles |
| Color | Matching beam |
| Intensity | Builds over time |

#### Puzzle Solve
| Property | Value |
|----------|-------|
| Type | Burst + trail |
| Color | Gold |
| Direction | Toward mechanism |

---

### Pressure Plates

#### Plate Activated
| Property | Value |
|----------|-------|
| Type | Glow on symbols |
| Color | Gold |
| Particles | Light dust |

#### Mechanism Triggered
| Property | Value |
|----------|-------|
| Type | Energy transfer |
| Direction | Plate → Connected object |

---

### Water Puzzles

#### Water Flow
| Property | Value |
|----------|-------|
| Type | Niagara fluid |
| Particles | Splash, mist |
| Direction | Follow channels |

#### Water Wheel Active
| Property | Value |
|----------|-------|
| Type | Spray particles |
| Color | Blue-white |

---

### Growth/Decay

#### Growth Effect
| Property | Value |
|----------|-------|
| Type | Organic expansion |
| Particles | Green energy, leaves |
| Color | Vibrant green |
| Duration | 1-2 sec |

#### Decay Effect
| Property | Value |
|----------|-------|
| Type | Withering collapse |
| Particles | Dark energy, dead leaves |
| Color | Brown → Purple |
| Duration | 1-2 sec |

---

## UI VFX

### Health/Stamina Bars
| Effect | Trigger |
|--------|---------|
| Fill animation | On change |
| Low health pulse | Health < 25% |
| Damage flash | Taking damage |
| Heal glow | Gaining health |

### Collectible Pickup
| Effect | Description |
|--------|-------------|
| Spirit Essence | Burst + trail to UI |
| Lore Stone | Radial glow |
| Guardian Relic | Grand burst |

### Interaction Prompt
| Effect | Description |
|--------|-------------|
| Fade in/out | Smooth transition |
| Gentle pulse | Draws attention |

---

## Technical Specifications

### Performance Targets
| Metric | Target |
|--------|--------|
| Max concurrent particles | 5,000 |
| Max emitter per effect | 5 |
| GPU particle preference | Yes |
| LOD distance | Auto-reduce at 50m+ |

### Niagara Best Practices
- Use GPU particles where possible
- Implement LOD for distant effects
- Pool commonly used effects
- Avoid per-particle collision for large counts

### Material Guidelines
- Additive blend for glows
- Translucent for smoke/fog
- Masked for hard-edged particles
- Distortion for heat/reality warps

---

## Priority List

### Must Have (MVP)
- [ ] Player hit impacts
- [ ] Weapon trails
- [ ] Enemy death effects
- [ ] Collectible pickups
- [ ] Basic environmental particles
- [ ] Puzzle feedback effects

### Should Have
- [ ] Full boss effects
- [ ] Ghost echo system
- [ ] Growth/decay abilities
- [ ] Polish particle details

### Nice to Have
- [ ] Advanced environment particles
- [ ] Reality distortion (Area 3)
- [ ] Dynamic corruption spread
- [ ] Full restoration sequence

---

*VFX should enhance, not distract. Every effect serves a purpose—feedback, atmosphere, or storytelling.*

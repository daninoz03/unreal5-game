# 🎵 Asset Requirements: Audio

**Document Version**: 1.0  
**Audio Format**: WAV (source), compressed in engine  
**Sample Rate**: 48kHz  
**Bit Depth**: 24-bit (source), 16-bit (final)  

---

## Audio Direction

### Overall Tone
The audio should feel **organic and mystical**. Natural sounds blend with subtle magical elements. Music supports emotion without overpowering.

### Audio Pillars
1. **Nature is alive** - The forest breathes, whispers, reacts
2. **Magic has sound** - Subtle, ethereal, not sci-fi
3. **Impact matters** - Combat should feel weighty
4. **Less is more** - Silence can be powerful

---

## Music

### Music Style Guide

| Situation | Instrumentation | Tempo | Notes |
|-----------|-----------------|-------|-------|
| Exploration | Strings, woodwinds, soft piano | Slow-Medium | Ambient, spacious |
| Discovery | Swelling orchestra | Builds | Wonder, reveal |
| Combat | Percussion, brass, intense strings | Fast | Driving, tense |
| Puzzle | Minimal piano, soft pads | Slow | Thoughtful |
| Boss Fight | Full orchestra + choir | Variable | Epic, emotional |
| Victory | Triumphant brass, release | Medium | Relief, accomplishment |
| Emotional | Solo voice, piano | Slow | Grandmother scenes |
| Credits | Main theme, full arrangement | Medium | Reflective |

---

### Music Tracks Needed

#### Main Theme
- Full orchestral arrangement (2-3 minutes)
- Piano solo version (for emotional moments)
- Music box version (for lore stones)

#### Area Themes

**Sacred Grove**
| Track | Duration | Loop |
|-------|----------|------|
| Grove Exploration | 3-4 min | Yes |
| Grove Discovery | 30 sec | No (stinger) |
| Grove Combat | 2 min | Yes |
| Grove Tension | 2 min | Yes |

**Ancient Ruins**
| Track | Duration | Loop |
|-------|----------|------|
| Ruins Exploration | 4 min | Yes |
| Ruins Mystery | 3 min | Yes |
| Ruins Combat | 2 min | Yes |
| Treant Battle | 3 min | Yes (phase transitions) |
| Revelation (story) | 1 min | No |

**Heart of the Forest**
| Track | Duration | Loop |
|-------|----------|------|
| Heart Approach | 3 min | Yes |
| Heart Tension | 2 min | Yes |
| Final Boss Phase 1 | 2 min | Yes |
| Final Boss Phase 2 | 2 min | Yes |
| Final Boss Phase 3 | 2 min | Yes |
| Victory/Resolution | 2 min | No |

#### Emotional Cues
| Track | Duration | Use |
|-------|----------|-----|
| Grandmother's Theme | 2 min | Lore stones, revelations |
| Loss | 1 min | Sad discoveries |
| Hope | 1 min | Restoration moments |

---

## Sound Effects

### Player Character - Kira

#### Movement
| Sound | Variations | Notes |
|-------|------------|-------|
| Footstep (grass) | 5+ | Soft, natural |
| Footstep (stone) | 5+ | Harder impact |
| Footstep (wood) | 5+ | Hollow resonance |
| Footstep (water) | 5+ | Splash |
| Sprint breathing | 3 | Exertion loops |
| Jump grunt | 3 | Effort |
| Land (soft) | 3 | Grass/dirt |
| Land (hard) | 3 | Stone |
| Ledge grab | 2 | Grip + effort |
| Climb shuffle | 3 | Movement on surface |
| Dodge roll | 2 | Whoosh + cloth |

#### Combat
| Sound | Variations | Notes |
|-------|------------|-------|
| Staff swing (light) | 3 | Quick whoosh |
| Staff swing (heavy) | 2 | Slower, weightier |
| Staff impact (flesh) | 3 | Meaty hit |
| Staff impact (miss) | 2 | Air whoosh |
| Charged attack buildup | 1 | Building energy |
| Charged attack release | 1 | Powerful impact |
| Take damage (light) | 3 | Pain grunt |
| Take damage (heavy) | 2 | Larger reaction |
| Death | 1 | Final breath |

#### Vocalizations
| Sound | Variations | Notes |
|-------|------------|-------|
| Effort grunt | 5 | Various exertions |
| Pain reaction | 3 | Getting hit |
| Discovery "hmm" | 2 | Finding something |
| Success "yes" | 2 | Solving puzzles |
| Frustration | 2 | Failed attempts |

---

### Enemies

#### Blighted Wolf
| Sound | Variations | Notes |
|-------|------------|-------|
| Idle growl | 3 | Ambient menace |
| Alert bark | 2 | Spotted player |
| Lunge attack | 2 | Movement + snarl |
| Bite attack | 2 | Snap |
| Take damage | 3 | Yelp |
| Death | 2 | Corruption dispersing |
| Ambient corruption | 1 | Loop, subtle dark sound |

#### Corrupted Treant
| Sound | Variations | Notes |
|-------|------------|-------|
| Ambient creak | 3 | Wood groaning |
| Roar/alert | 1 | Sees player |
| Ground slam charge | 1 | Building |
| Ground slam impact | 1 | Massive thud + debris |
| Swipe attack | 2 | Wood whoosh |
| Root eruption | 1 | Ground breaking |
| Take damage | 3 | Wood cracking |
| Stagger | 1 | Vulnerability state |
| Death | 1 | Collapse + purification |
| Core exposed | 1 | Magical vulnerability |

#### Blighted Heart (Boss)
| Sound | Variations | Notes |
|-------|------------|-------|
| Ambient pulse | 1 | Heartbeat loop |
| Root attack | 2 | Ground eruption |
| Corruption wave | 1 | Dark energy spread |
| Dark pulse charge | 1 | Gathering darkness |
| Dark pulse release | 1 | Explosion |
| Phase transition | 2 | State change |
| Memory assault | 1 | Disorienting sound |
| Defeat | 1 | Corruption leaving |

---

### Environment

#### Sacred Grove
| Sound | Type | Notes |
|-------|------|-------|
| Ambience base | Loop | Birds, wind, leaves |
| Wind gust | Random trigger | Occasional |
| Bird calls | Random | Various species |
| Stream flow | Loop | Near water |
| Waterfall | Loop | Louder near waterfall |
| Leaves rustling | Random | Movement |

#### Ancient Ruins
| Sound | Type | Notes |
|-------|------|-------|
| Ambience base | Loop | Echoes, drips, silence |
| Water drip | Random | Interior spaces |
| Stone creak | Random | Structure settling |
| Wind through gaps | Loop | Specific areas |
| Echo effect | Reverb | Interior spaces |

#### Heart of the Forest
| Sound | Type | Notes |
|-------|------|-------|
| Ambience base | Loop | Unstable, shifting |
| Reality distortion | Random | Glitch sounds |
| Memory whispers | Random | Ghostly voices |
| Corruption hum | Loop | Near corruption |
| Purification | Event | Light sounds |

#### Corruption Sounds
| Sound | Type | Notes |
|-------|------|-------|
| Corruption ambient | Loop | Dark hum, unsettling |
| Corruption spread | Event | Growing sound |
| Corruption impact | Event | Player touching |

---

### UI & Feedback

#### Menu/Interface
| Sound | Notes |
|-------|-------|
| Menu open | Soft |
| Menu close | Soft |
| Button hover | Subtle |
| Button select | Confirmation |
| Back/cancel | Gentle rejection |
| Slider adjust | Tick sounds |

#### Gameplay Feedback
| Sound | Notes |
|-------|-------|
| Health pickup | Positive, healing |
| Stamina recovery | Subtle breathing |
| Level up / upgrade | Achievement sound |
| Checkpoint reached | Soft chime |
| Save game | Subtle confirmation |
| Objective complete | Accomplishment |

#### Collectibles
| Sound | Notes |
|-------|-------|
| Spirit Essence pickup | Magical, bright |
| Lore Stone activate | Ancient, mystical |
| Lore Stone voice | Ethereal, layered |
| Guardian Relic | Grand, important |

---

### Puzzles

#### Beam Reflection
| Sound | Notes |
|-------|-------|
| Mirror rotate | Stone grinding |
| Beam activate | Light energy |
| Beam reflection | Ping on mirror |
| Receiver charging | Building energy |
| Puzzle solve | Success chime |

#### Pressure Plates
| Sound | Notes |
|-------|-------|
| Plate press | Stone movement |
| Plate release | Reverse |
| Mechanism activate | Gears/movement |

#### Water Puzzles
| Sound | Notes |
|-------|-------|
| Gate open/close | Wood + water |
| Water flow start | Rush |
| Water flow loop | Continuous |
| Water wheel turn | Mechanical + water |

#### Growth/Decay
| Sound | Notes |
|-------|-------|
| Growth ability | Nature magic |
| Plant growing | Organic stretch |
| Decay ability | Darker magic |
| Plant withering | Crumbling |

---

### Doors & Mechanisms
| Sound | Notes |
|-------|-------|
| Stone door open | Heavy, grinding |
| Stone door close | Reverse |
| Wood door open | Creaking |
| Metal gate | Metallic |
| Platform rise | Stone movement |
| Bridge extend | Wood/stone |

---

## Voice

### Kira Dialogue
- All written lines in StoryAndNarrative.md
- Approximately 50-75 lines total
- Mix of observation, reaction, and emotional delivery

### Lore Stone Voice
- 12 lore stone recordings
- Ethereal, layered effect (multiple voices in unison)
- Some processed for "ancient" feel

### Grandmother Voice (Flashback)
- Final lore stone message
- Warm but sad delivery
- Clear and present (not as processed)

---

## Technical Specifications

### File Formats
| Use | Format | Settings |
|-----|--------|----------|
| Source files | WAV | 48kHz, 24-bit |
| Music (in-engine) | OGG | Variable bitrate |
| SFX (in-engine) | WAV/OGG | 16-bit |
| Voice (in-engine) | OGG | High quality |

### Mixing Guidelines
| Category | Base Volume | Notes |
|----------|-------------|-------|
| Music | -12dB | Ducks during dialogue |
| Ambience | -18dB | Background bed |
| SFX | -6dB | Reference level |
| Voice | 0dB | Highest priority |

### Spatialization
- All environmental sounds: 3D spatial
- All combat sounds: 3D spatial
- Music: 2D (non-spatial)
- UI: 2D (non-spatial)
- Voice: 2D (non-spatial) or 3D (lore stones)

---

## Audio Middleware

**Recommended**: Unreal's built-in MetaSounds or Wwise (if scope expands)

### Sound Cue Requirements
- Randomized variation support
- Distance-based volume falloff
- Surface type detection for footsteps
- Music crossfade system
- Environmental reverb zones

---

## Priority List

### Must Have (MVP)
- [ ] Player footsteps (at least 3 surfaces)
- [ ] Basic combat sounds
- [ ] Exploration ambience (all areas)
- [ ] Core puzzle sounds
- [ ] Collectible pickups
- [ ] Exploration music (1-2 tracks)
- [ ] Combat music (1 track)

### Should Have
- [ ] Full voice recording
- [ ] All enemy sounds
- [ ] Complete music suite
- [ ] Environmental variety

### Nice to Have
- [ ] Boss-specific music
- [ ] Grandmother's voice
- [ ] Dynamic music system
- [ ] Full lore stone recordings

---

## Audio Sources

### Royalty-Free Libraries
- **Freesound.org** - SFX, ambiences
- **Incompetech** - Music
- **Epidemic Sound** - Music (subscription)

### Marketplace Assets
- Unreal Marketplace audio packs
- Nature/forest ambience packs

### Custom Creation
- All voice work
- Key musical themes
- Unique creature sounds
- Signature sounds (staff abilities, etc.)

---

*Audio creates 50% of the emotional experience. Don't underestimate its importance.*

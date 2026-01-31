# ⚔️ Blueprint: Combat System

**System**: Combat Mechanics & Enemy AI  
**Complexity**: Medium-High  
**Blueprint Types**: Character BP, AI Controller, Behavior Tree, Animation BP  

---

## Overview

The combat system handles player attacks, enemy behavior, damage calculation, and combat feedback. It's designed for impactful, readable encounters—quality over quantity.

---

## System Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                     COMBAT SYSTEM OVERVIEW                       │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│  ┌──────────────────┐    ┌──────────────────┐                   │
│  │  BP_KiraCharacter │    │  BP_EnemyBase    │                   │
│  │  (Player Combat)  │◄──►│  (Enemy Combat)  │                   │
│  └────────┬─────────┘    └────────┬─────────┘                   │
│           │                       │                              │
│           ▼                       ▼                              │
│  ┌──────────────────┐    ┌──────────────────┐                   │
│  │ Combat Component │    │  AI Controller    │                   │
│  │ (Damage, Combos) │    │  (Behavior Tree)  │                   │
│  └────────┬─────────┘    └────────┬─────────┘                   │
│           │                       │                              │
│           └───────────┬───────────┘                              │
│                       ▼                                          │
│              ┌──────────────────┐                                │
│              │  Damage System   │                                │
│              │  (Apply, React)  │                                │
│              └──────────────────┘                                │
│                                                                  │
└─────────────────────────────────────────────────────────────────┘
```

---

## Player Combat Component

### Component Variables

```
UC_PlayerCombat (Actor Component)
├── Variables:
│   ├── bIsAttacking (bool)
│   ├── bCanCombo (bool)
│   ├── ComboCount (int) - 0, 1, 2, 3
│   ├── ComboWindow (float) - Time allowed between hits
│   ├── CurrentComboTimer (float)
│   ├── bIsInvulnerable (bool)
│   ├── LightAttackDamage (float) - 15
│   ├── HeavyAttackDamage (float) - 35
│   ├── ChargedHeavyDamage (float) - 50
│   ├── AttackRange (float) - 150
│   └── LockedTarget (Actor Reference)
│
├── Functions:
│   ├── LightAttack()
│   ├── HeavyAttack()
│   ├── ProcessCombo()
│   ├── ResetCombo()
│   ├── ApplyDamage()
│   └── TryLockTarget()
│
└── Events:
    ├── OnAttackStart
    ├── OnAttackEnd
    ├── OnComboAdvance
    └── OnDamageDealt
```

---

## Light Attack System

### Light Attack Flow

```
┌─────────────────────────────────────────────────────────────┐
│ Light Attack Handler                                        │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  [IA_LightAttack Triggered]                                 │
│         │                                                   │
│         ▼                                                   │
│  ┌──────────────────┐                                       │
│  │ Can Attack?      │                                       │
│  │ (!bIsAttacking   │                                       │
│  │  OR bCanCombo)   │                                       │
│  └────────┬─────────┘                                       │
│      Yes  │  No                                             │
│           ▼  ▼                                              │
│    [Process Attack]  [Queue Input / Ignore]                 │
│         │                                                   │
│         ▼                                                   │
│  ┌──────────────────┐                                       │
│  │ ComboCount?      │                                       │
│  └────────┬─────────┘                                       │
│     0     │  1     │  2     │  3                            │
│           ▼        ▼        ▼        ▼                      │
│    [Attack 1] [Attack 2] [Attack 3] [Reset Combo]           │
│    (15 dmg)   (15 dmg)   (20 dmg)   [Attack 1]              │
│         │                                                   │
│         ▼                                                   │
│  [Play Attack Montage (ComboCount)]                         │
│         │                                                   │
│         ▼                                                   │
│  [Set bIsAttacking = True]                                  │
│         │                                                   │
│         ▼                                                   │
│  [Spawn Hit Detection]                                      │
│         │                                                   │
│         ▼                                                   │
│  [On Montage Notify: "ComboWindow"]                         │
│         │                                                   │
│         ▼                                                   │
│  [Set bCanCombo = True]                                     │
│  [Start Combo Timer]                                        │
│         │                                                   │
│         ▼                                                   │
│  [On Montage End OR Timer Expire]                           │
│         │                                                   │
│         ▼                                                   │
│  ┌──────────────────┐                                       │
│  │ Input Queued?    │                                       │
│  └────────┬─────────┘                                       │
│      Yes  │  No                                             │
│           ▼  ▼                                              │
│   [Advance Combo]  [Reset Combo]                            │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Combo Timing

```
Attack Timeline:
         
Light 1  ├────[Windup]───[Strike]───[Recovery]───[Combo Window]───┤
         0ms           150ms      300ms         450ms           650ms
                                    │                              │
                                    └── Hit Detection ──────────────┘
                                    └── Can input next attack ──────┘

Light 2  ├────[Windup]───[Strike]───[Recovery]───[Combo Window]───┤
         0ms           100ms      250ms         400ms           600ms

Light 3  ├────[Windup]───[Strike]─────[Long Recovery]─────────────┤
         0ms           200ms      400ms                        800ms
                                                                   │
                                                     Combo Resets ─┘
```

---

## Heavy Attack System

### Heavy Attack Flow

```
┌─────────────────────────────────────────────────────────────┐
│ Heavy Attack Handler                                        │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  [IA_HeavyAttack Started]                                   │
│         │                                                   │
│         ▼                                                   │
│  [Set bChargingHeavy = True]                                │
│         │                                                   │
│         ▼                                                   │
│  [Start Charge Timer]                                       │
│         │                                                   │
│         ▼                                                   │
│  [Play Charge Animation]                                    │
│         │                                                   │
│         ▼                                                   │
│  [While Held: Accumulate Charge]                            │
│         │                                                   │
│  ─────────────────────────────────────────────────────────  │
│                                                             │
│  [IA_HeavyAttack Completed / Released]                      │
│         │                                                   │
│         ▼                                                   │
│  ┌──────────────────┐                                       │
│  │ Charge Time?     │                                       │
│  └────────┬─────────┘                                       │
│    < 0.5s │  >= 0.5s                                        │
│           ▼        ▼                                        │
│    [Normal Heavy]  [Charged Heavy]                          │
│    (35 dmg)        (50 dmg)                                 │
│         │               │                                   │
│         └───────┬───────┘                                   │
│                 ▼                                           │
│  [Play Heavy Attack Montage]                                │
│                 │                                           │
│                 ▼                                           │
│  [Large Hit Detection Sphere]                               │
│                 │                                           │
│                 ▼                                           │
│  [Consume Stamina: HeavyAttackCost]                         │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

---

## Hit Detection System

### Sphere Trace for Hits

```
┌─────────────────────────────────────────────────────────────┐
│ Hit Detection (Called from Animation Notify)                │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  [Anim Notify: "EnableHitDetection"]                        │
│         │                                                   │
│         ▼                                                   │
│  [Get Weapon Socket Location]                               │
│         │                                                   │
│         ▼                                                   │
│  [Sphere Trace: Start → End]                                │
│  │  • Radius: 30 (Light) / 50 (Heavy)                       │
│  │  • Channel: EnemyHitable                                 │
│  │  • Ignore: Self                                          │
│         │                                                   │
│         ▼                                                   │
│  ┌──────────────────┐                                       │
│  │ Hit Results?     │                                       │
│  └────────┬─────────┘                                       │
│      Yes  │  No                                             │
│           ▼  ▼                                              │
│    [For Each Hit]  [No Damage]                              │
│         │                                                   │
│         ▼                                                   │
│  ┌──────────────────┐                                       │
│  │ Already Hit      │ (Prevent multi-hit same target)       │
│  │ This Swing?      │                                       │
│  └────────┬─────────┘                                       │
│       No  │  Yes                                            │
│           ▼  ▼                                              │
│    [Apply Damage]  [Skip]                                   │
│         │                                                   │
│         ▼                                                   │
│  [Add to HitThisSwing Array]                                │
│         │                                                   │
│         ▼                                                   │
│  [Spawn Hit VFX at Impact Point]                            │
│         │                                                   │
│         ▼                                                   │
│  [Play Hit Sound]                                           │
│         │                                                   │
│         ▼                                                   │
│  [Camera Shake (small)]                                     │
│         │                                                   │
│         ▼                                                   │
│  [Hitstop: 0.05 sec] (subtle time freeze)                   │
│                                                             │
│  ─────────────────────────────────────────────────────────  │
│                                                             │
│  [Anim Notify: "DisableHitDetection"]                       │
│         │                                                   │
│         ▼                                                   │
│  [Clear HitThisSwing Array]                                 │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

---

## Damage System

### Damage Application

```
┌─────────────────────────────────────────────────────────────┐
│ Apply Damage Function                                       │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  [Function: ApplyDamageToTarget]                            │
│  Inputs: Target (Actor), BaseDamage (Float),                │
│          DamageType (Enum), Instigator (Actor)              │
│         │                                                   │
│         ▼                                                   │
│  [Get Target's Health Component]                            │
│         │                                                   │
│         ▼                                                   │
│  ┌──────────────────┐                                       │
│  │ Target has       │                                       │
│  │ HealthComponent? │                                       │
│  └────────┬─────────┘                                       │
│      Yes  │  No                                             │
│           ▼  ▼                                              │
│    [Calculate Final   [Return]                              │
│     Damage]                                                 │
│         │                                                   │
│         ▼                                                   │
│  [Apply Damage Modifiers]                                   │
│  │  • Critical Hit? (random chance)                         │
│  │  • Weak Point Hit? (if applicable)                       │
│  │  • Resistance? (enemy type)                              │
│         │                                                   │
│         ▼                                                   │
│  [Call: Target.ReceiveDamage(FinalDamage)]                  │
│         │                                                   │
│         ▼                                                   │
│  [Broadcast: OnDamageDealt Event]                           │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Damage Reception (Target Side)

```
┌─────────────────────────────────────────────────────────────┐
│ Receive Damage Function (On Target)                         │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  [Event: ReceiveDamage]                                     │
│  Input: DamageAmount (Float), DamageInfo (Struct)           │
│         │                                                   │
│         ▼                                                   │
│  ┌──────────────────┐                                       │
│  │ bIsInvulnerable? │                                       │
│  └────────┬─────────┘                                       │
│      Yes  │  No                                             │
│           ▼  ▼                                              │
│    [Return]  [Continue]                                     │
│                 │                                           │
│                 ▼                                           │
│  [CurrentHealth -= DamageAmount]                            │
│                 │                                           │
│                 ▼                                           │
│  [Clamp Health: 0 to MaxHealth]                             │
│                 │                                           │
│                 ▼                                           │
│  [Play Hit Reaction Animation]                              │
│                 │                                           │
│                 ▼                                           │
│  [Spawn Damage Number UI]                                   │
│                 │                                           │
│                 ▼                                           │
│  ┌──────────────────┐                                       │
│  │ CurrentHealth    │                                       │
│  │ <= 0?            │                                       │
│  └────────┬─────────┘                                       │
│      Yes  │  No                                             │
│           ▼  ▼                                              │
│    [Call: Die()]  [Update Health Bar]                       │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

---

## Enemy AI System

### Enemy Base Blueprint

```
BP_EnemyBase (Character)
├── Components:
│   ├── Health Component
│   ├── AI Perception (Sight, Hearing)
│   ├── Widget Component (Health Bar)
│   └── Behavior Tree Reference
│
├── Variables:
│   ├── MaxHealth (float)
│   ├── CurrentHealth (float)
│   ├── AttackDamage (float)
│   ├── AttackRange (float)
│   ├── DetectionRange (float)
│   ├── bIsAggro (bool)
│   ├── HomeLocation (Vector)
│   └── CurrentTarget (Actor)
│
├── Functions:
│   ├── ReceiveDamage()
│   ├── Die()
│   ├── Attack()
│   ├── ReturnToHome()
│   └── SetAggro()
│
└── Events:
    ├── OnPerceptionUpdated
    ├── OnDamageReceived
    └── OnDeath
```

### Behavior Tree: Blighted Wolf

```
┌─────────────────────────────────────────────────────────────┐
│ BT_BlightedWolf                                             │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  [ROOT]                                                     │
│     │                                                       │
│     └─[SELECTOR]                                            │
│           │                                                 │
│           ├─[SEQUENCE: Combat]                              │
│           │     │                                           │
│           │     ├─[Decorator: Has Target?]                  │
│           │     │                                           │
│           │     ├─[Selector: Attack or Approach]            │
│           │     │     │                                     │
│           │     │     ├─[Sequence: Attack]                  │
│           │     │     │     ├─[Decorator: In Range?]        │
│           │     │     │     ├─[Task: Face Target]           │
│           │     │     │     ├─[Task: Telegraph Attack]      │
│           │     │     │     ├─[Wait: 0.5s]                  │
│           │     │     │     ├─[Task: Execute Attack]        │
│           │     │     │     └─[Wait: Recovery 1.0s]         │
│           │     │     │                                     │
│           │     │     └─[Sequence: Approach]                │
│           │     │           ├─[Task: Move To Target]        │
│           │     │           └─[Task: Circle Strafe]         │
│           │     │                                           │
│           │     └─[Task: Update Target]                     │
│           │                                                 │
│           ├─[SEQUENCE: Patrol]                              │
│           │     │                                           │
│           │     ├─[Decorator: No Target]                    │
│           │     ├─[Task: Get Patrol Point]                  │
│           │     ├─[Task: Move To Point]                     │
│           │     └─[Wait: 2-5s random]                       │
│           │                                                 │
│           └─[SEQUENCE: Idle]                                │
│                 │                                           │
│                 ├─[Task: Return to Home]                    │
│                 └─[Task: Play Idle Animation]               │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Wolf Attack Pattern

```
┌─────────────────────────────────────────────────────────────┐
│ Wolf Attack Execution                                       │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  [Task: ExecuteAttack]                                      │
│         │                                                   │
│         ▼                                                   │
│  [Select Attack Type]                                       │
│  │  • 70%: Lunge Attack                                     │
│  │  • 30%: Bite Attack                                      │
│         │                                                   │
│         ▼                                                   │
│  [Play Telegraph Animation]                                 │
│  │  • Lunge: Crouch + Growl (0.5s)                          │
│  │  • Bite: Head lower + Snarl (0.3s)                       │
│         │                                                   │
│         ▼                                                   │
│  [Execute Attack]                                           │
│  │  • Lunge: Launch toward target, damage on contact        │
│  │  • Bite: Quick damage if in range                        │
│         │                                                   │
│         ▼                                                   │
│  [Post-Attack State]                                        │
│  │  • Lunge: 1.0s vulnerability (key punish window)         │
│  │  • Bite: 0.5s recovery                                   │
│         │                                                   │
│         ▼                                                   │
│  [Return to Behavior Tree]                                  │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

---

## Mini-Boss: Corrupted Treant

### Behavior Tree: Treant

```
┌─────────────────────────────────────────────────────────────┐
│ BT_CorruptedTreant                                          │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  [ROOT]                                                     │
│     │                                                       │
│     └─[SELECTOR]                                            │
│           │                                                 │
│           ├─[SEQUENCE: Rage Mode] (HP < 50%)                │
│           │     ├─[Task: Faster Attacks]                    │
│           │     ├─[Task: Add Root Eruption]                 │
│           │     └─[Task: Reduce Recovery Times]             │
│           │                                                 │
│           ├─[SEQUENCE: Combat]                              │
│           │     │                                           │
│           │     ├─[Selector: Choose Attack]                 │
│           │     │     │                                     │
│           │     │     ├─[Sequence: Ground Slam]             │
│           │     │     │     ├─[Decorator: Cooldown 5s]      │
│           │     │     │     ├─[Task: Telegraph (3s)]        │
│           │     │     │     ├─[Task: Execute Slam]          │
│           │     │     │     ├─[Task: Expose Core (1.5s)]    │
│           │     │     │     └─[Task: Recovery]              │
│           │     │     │                                     │
│           │     │     ├─[Sequence: Wide Swipe]              │
│           │     │     │     ├─[Decorator: Player Close]     │
│           │     │     │     ├─[Task: Telegraph (1s)]        │
│           │     │     │     └─[Task: Execute Swipe]         │
│           │     │     │                                     │
│           │     │     └─[Sequence: Root Eruption]           │
│           │     │           ├─[Decorator: Cooldown 8s]      │
│           │     │           ├─[Task: Telegraph (2s)]        │
│           │     │           └─[Task: Spawn Root Hazards]    │
│           │     │                                           │
│           │     └─[Task: Face Player]                       │
│           │                                                 │
│           └─[SEQUENCE: Idle]                                │
│                 └─[Task: Ambient Animation]                 │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Treant Vulnerability System

```
┌─────────────────────────────────────────────────────────────┐
│ Treant Core Vulnerability                                   │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  [After Ground Slam]                                        │
│         │                                                   │
│         ▼                                                   │
│  [Set bCoreExposed = True]                                  │
│         │                                                   │
│         ▼                                                   │
│  [Enable Core Collision (separate hit box)]                 │
│         │                                                   │
│         ▼                                                   │
│  [Play Core Glow VFX]                                       │
│         │                                                   │
│         ▼                                                   │
│  [Start Timer: 1.5 seconds]                                 │
│         │                                                   │
│         ▼                                                   │
│  [Core Hit Detection Active]                                │
│  │  • Damage to core: 2x multiplier                         │
│  │  • Triggers stagger animation if threshold met           │
│         │                                                   │
│         ▼                                                   │
│  [Timer Expires OR Stagger Triggered]                       │
│         │                                                   │
│         ▼                                                   │
│  [Set bCoreExposed = False]                                 │
│         │                                                   │
│         ▼                                                   │
│  [Return to Normal Behavior]                                │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

---

## Combat Feedback Systems

### Hit Feedback

```
On Successful Hit:
├── Visual:
│   ├── Hit VFX at impact point
│   ├── Enemy flash white (0.05s)
│   ├── Damage number popup
│   └── Screen shake (intensity based on damage)
│
├── Audio:
│   ├── Impact sound (varies by enemy type)
│   ├── Enemy pain vocalization
│   └── Weapon "whoosh" on swing
│
└── Feel:
    ├── Hitstop (0.03-0.08s based on attack weight)
    ├── Controller rumble
    └── Slight camera punch
```

### Taking Damage Feedback

```
On Player Hit:
├── Visual:
│   ├── Screen flash red (edge vignette)
│   ├── Health bar pulse
│   ├── Kira hit reaction animation
│   └── Blood/impact VFX (stylized)
│
├── Audio:
│   ├── Impact sound
│   ├── Kira pain vocalization
│   └── Heartbeat if low health
│
└── Feel:
    ├── Controller rumble (strong)
    ├── Brief movement slow (0.1s)
    └── Camera shake
```

---

## Damage Values Reference

### Player Attacks

| Attack | Base Damage | Stamina Cost | Notes |
|--------|-------------|--------------|-------|
| Light 1 | 15 | 10 | Fast |
| Light 2 | 15 | 10 | Fast |
| Light 3 | 20 | 10 | Slight delay, more range |
| Heavy | 35 | 25 | Slow, good range |
| Charged Heavy | 50 | 40 | Very slow, AoE |
| Dodge Attack | 20 | 15 | Quick follow-up |

### Enemy Attacks

| Enemy | Attack | Damage | Telegraph | Recovery |
|-------|--------|--------|-----------|----------|
| Wolf | Lunge | 15 | 0.5s | 1.0s (PUNISH) |
| Wolf | Bite | 10 | 0.3s | 0.5s |
| Alpha Wolf | Lunge | 20 | 0.5s | 0.8s |
| Alpha Wolf | Howl | 0 | 1.0s | Buffs pack |
| Treant | Slam | 30 | 3.0s | 1.5s (CORE) |
| Treant | Swipe | 20 | 1.0s | 0.5s |
| Treant | Roots | 15/sec | 2.0s | Area denial |

---

## Implementation Order

1. **Player Light Attack** (single hit first)
2. **Hit Detection System**
3. **Damage System**
4. **Enemy Base + Health**
5. **Light Attack Combo**
6. **Heavy Attack**
7. **Wolf AI**
8. **Combat Feedback**
9. **Treant Boss**

---

*Combat should feel impactful and readable. Every attack should have clear tells and windows.*

# Combat System Demo (C++)

A small, tick-based combat simulation designed to explore gameplay
systems such as abilities, cooldowns, and status effects.

This project focuses on **systems structure and behavior over time**
rather than player input or rendering.

## Overview

The simulation features two entities (a Player and a Skeleton) that
engage in combat using abilities with cooldowns. One ability applies a
damage-over-time effect (Bleed) that refreshes its duration rather than
stacking.

Combat is simulated in fixed time steps, and output is written to a
combat log that can be configured to print at different intervals.

## Key Concepts Demonstrated

- Entity-based combat model
- Modular ability system with cooldown tracking
- Time-based status effects with refresh behavior
- Deterministic update loop
- Separation of simulation logic from presentation (combat logging)

## Design Notes

- `Entity` owns stats and active effects but does not contain combat rules.
- `Ability` encapsulates actions and cooldown timing.
- `StatusEffect` handles time-based behavior independently of abilities.
- Combat logging is decoupled from simulation so log frequency can change
  without affecting combat behavior.

The system is designed to be easily extensible with new abilities,
effects, or entity types.

## Building & Running

Requires a C++20-compatible compiler (e.g., g++).


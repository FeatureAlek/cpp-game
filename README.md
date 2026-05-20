# Project Plan – "Fireboy and Watergirl inspired game"

## P0 – Team Formation (Week 8)

- Team name: Procrastinators
- Team members: Faustas Alekna, Gustas Juškevičius
- Team captain: Gustas Juškevičius
- Project theme: 2D cooperative puzzle-platformer game
- Scope: One level (for now)

---

## P1 – Project Vision (Week 10)

### Short Description
Single-level (for now) 2D cooperative puzzle-platformer where two characters with different elemental traits must reach the exit by solving simple puzzles by interacting with the environment.

### High-Level Structure
- Core systems: game loop, input, movement, collisions
- Entities: two players, objects, hazards, exit
- Level: one handcrafted tile-based map
- Interactions: buttons, doors, simple traps

### Basic Flow
1. Load the level  
2. Players move and interact
3. Solve simple puzzles  
4. Both reach the exit  
5. Level ends

### Used infrastructure
- CMake for building

https://cmake.org/

- SFML (v2.6.1 to be specific) as a C++ 2D graphics library

https://www.sfml-dev.org/
https://github.com/SFML/SFML

### Proof of Concept
- Window opens  
- Two placeholder character move with different keyboard input


## P2 – Back-End Development (Week 14)
- Player movement and collisions
- Level loading
- Basic objects (platform, door)
- Hazards
- Simple game state handling
- Minimal tests for movement, interaction, and level completion

---

## P3 – Front-End / GUI (Week 16)
- Basic sprites and animations
- Simple menu (start/restart)
- Background and tiles
- Optional sound effects
- HUD elements
- Add visual polish and user interface.

---

## Summary of Stages

| Stage | Goal |
|-------|------|
| P0 | Team + topic |
| P1 | Vision + PoC |
| P2 | Core gameplay logic |
| P3 | Visuals + UI |

## Report
[Report excel file  (click here)](./Ataskaita.xlsx)

---

## Configuration (settings)

Users are free to change Config.hpp and treat it as settings (However we advise against doing so, as the functionality of the game may be harmed).

This includes:
- changing window width and height
- changing FPS limit
- changing player characteristics (speed, gravity, jump)
- chaging player sprite behaviour

and more. 

## Launching the game
Building and launching the game requires a build folder, which differs per operational system (and precisely for this reason does not exist on github) as well as to have SFML version 2.6.1 (not sure about later versions) and cmake

### bash
```bash
mkdir build && cd build
cmake ..
make run
```
### cmd
```cmd
cd build
make run
```
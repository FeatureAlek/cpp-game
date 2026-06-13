# Project Plan – "Fireboy and Watergirl inspired game"

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
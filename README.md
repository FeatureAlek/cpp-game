# Project Plan – "Fireboy and Watergirl inspired game"

### Short Description
2D cooperative puzzle-platformer where two characters with different elemental traits must reach the exit by solving simple puzzles by interacting with the environment.

### Used infrastructure
- CMake for building

https://cmake.org/

- SFML (v2.6.1 to be specific) as a C++ 2D graphics library

https://www.sfml-dev.org/
https://github.com/SFML/SFML

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

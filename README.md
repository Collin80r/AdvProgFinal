# AdvProgFinal
## Prerequisites
 * CMake (https://cmake.org/download/)
## Installation
 1. Clone this project
 2. Open command prompt inside project directory
 3. Get local SDL clone
 ```sh
 git clone https://github.com/libsdl-org/SDL.git vendored/SDL
 ```
 4. Configure & Build
 ```sh
 cmake -S . -B build
 cmake --build build
 ```
 5. Run
 ```sh
 ./build/Debug/main
 ```

## Additional Resources
Building with CMake: https://github.com/libsdl-org/SDL/blob/main/docs/INTRO-cmake.md

# AdvProgFinal
## Installation
 1. Install cmake (https://cmake.org/download/)
 2. Clone this project
 3. Open command prompt inside project directory
 4. Get local SDL clone
 ```sh
 git clone https://github.com/libsdl-org/SDL.git vendored/SDL
 ```
 3. Configure & Build
 ```sh
 cmake -S . -B build
 cmake --build build
 ```
 3. Run
 ```sh
 ./build/Debug/main
 ```

## Additional Resources
Building with CMake: https://github.com/libsdl-org/SDL/blob/main/docs/INTRO-cmake.md

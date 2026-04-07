# Snake Game in C++

This repository contains a simple Snake game project written in C++ with two playable versions:

- A console version built with standard Windows console APIs.
- A graphical version built with SFML when the library is installed.

The project is set up with CMake, so it can be opened in Visual Studio or built from the command line.

## Project Overview

The goal of this project is to provide a lightweight Snake game implementation that is easy to read, build, and extend. It is a good beginner-friendly C++ project for learning:

- Basic game loops
- Keyboard input handling
- Collision detection
- Score tracking
- Simple rendering in both console and windowed modes

## Included Versions

### 1. Console Version

The console game is implemented in `snake_console.cpp`.

Features:

- Grid-based snake movement
- Fruit collection
- Score system
- Snake tail growth
- Wall collision detection
- Self-collision detection
- Keyboard controls with `W`, `A`, `S`, `D`

### 2. SFML Window Version

The graphical game is implemented in `main.cpp`.

Features:

- Windowed rendering using SFML
- Snake and food drawn as rectangles
- Score display
- Restart option with the space bar
- Food respawn logic that avoids spawning on the snake

Note:
The SFML version is only built when SFML 2.5 or newer is installed and discoverable by CMake.

## Project Structure

```text
snake-game/
|-- CMakeLists.txt
|-- main.cpp
|-- snake_console.cpp
|-- README.md
```

## Requirements

### For the Console Version

- Windows
- A C++17-compatible compiler
- CMake 3.16 or newer

### For the SFML Version

- All of the above
- SFML 2.5 or newer installed on the system
- `SFMLConfig.cmake` available through `CMAKE_PREFIX_PATH` or `SFML_DIR`

## Build Instructions

### Configure

```powershell
cmake -S . -B build
```

### Build

```powershell
cmake --build build --config Debug
```

## Run Instructions

### Run the Console Version

```powershell
.\build\Debug\SnakeConsole.exe
```

### Run the SFML Version

If SFML is installed and detected by CMake, the `SnakeGame` target will also be generated:

```powershell
.\build\Debug\SnakeGame.exe
```

## Controls

### Console Version

- `W`: Move up
- `A`: Move left
- `S`: Move down
- `D`: Move right
- `X`: Exit the game

### SFML Version

- Arrow keys: Move the snake
- `Space`: Restart after game over

## Notes

- The console version currently builds without any external dependencies.
- The CMake configuration has been set up so the project still configures successfully even if SFML is not installed.
- The `build/` directory is generated output and should not be committed.

## Possible Improvements

- Add a start screen
- Add difficulty levels
- Add pause/resume support
- Improve the SFML UI and layout
- Prevent impossible reverse movement in the console version
- Add cross-platform console support

## Author

Created as a C++ Snake game practice project.

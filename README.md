# CharlieDeck32

A minimalist handheld console powered by an STM32 microcontroller and a Charlieplexed LED matrix, capable of running retro-style games like Flappy Bird, Snake, Pong and Tetris.

## Table of Contents

1. [Features](#features)
2. [Hardware Overview](#hardware-overview)
3. [Software & Build Instructions](#software--build-instructions)
4. [Games Included](#games-included)
5. [Project Roadmap & TODOs](#project-roadmap--todos)
6. [License](#license)

## Features

* Ultra-compact and portable. No LCD, just LEDs.
* Powered by STM32 MCU
* Efficient LED control via [Charlieplexing](https://en.wikipedia.org/wiki/Charlieplexing): drives many LEDs using few pins.
* Plays classic games like Flappy Bird, Snake, Pong and Tetris and possibly more
* Open-source under the **GPL-3.0 license**.

## Hardware Overview

**DIAGRAM HERE**

## Software & Build Instructions

### Prerequisites

* CMake
* MinGW
* SWD programmer (ST-Link, etc.)
* Optional: STM32 development toolchain (STM32CubeMX + HAL) for further development

### Building (using CMake and MinGW)

```bash
# --- Clone the repo and navigate into it ---
git clone https://github.com/chieftain0/CharlieDeck32.git
cd CharlieDeck32

# --- Create a build directory and navigate into it ---
mkdir build
cd build

# --- Create a separate Debug and Release build directories ---
mkdir Debug & mkdir Release

# --- Debug build ---
cd Debug
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ../..
mingw32-make

# --- Leave the Debug build directory ---
cd ..

# --- Release build ---
cd Release
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ../..
mingw32-make
```

### Flashing

* Connect your programmer (ST-Link, etc.)
* Flash the firmware using your preferred method:

    ```bash
    st-flash write CharlieDeck32.elf 0x8000000
    ```

    or use STM32CubeProgrammer for a GUI approach.

## Games Included

* **Flappy Bird** — tap to flap, dodge obstacles.
* **Snake** — collect dots, do not bite yourself.
* **PvP Pong** — two players, two paddles, one ball.
* **Tetris** — classic tetris.

## Project Roadmap & TODOs

* Make Snake food spawning non-blocking.  
* Make LED display function non-blocking.  
* Program the Tetris game.

## License

This project is licensed under the **GPL-3.0** license.

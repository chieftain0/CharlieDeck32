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

* [Git](https://git-scm.com/downloads)

* Optional: [MSYS2](https://www.msys2.org/) for Windows

* Compile toolchains:

  * For Windows: [MinGW-W64](https://github.com/niXman/mingw-builds-binaries/releases)

    MSYS2 (MinGW64):

    ```bash
    pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb
    ```

  * For Linux:

    ```bash
    sudo apt update
    sudo apt install build-essential
    ```

* [STM32CubeCLT](https://www.st.com/en/development-tools/STM32CubeCLT)

  * Contains the `arm-none-eabi-gcc` and `arm-none-eabi-g++` compilers which can be installed separately (see below). Nevertheless, STM32CubeCLT is strongly recommended.
  * For Windows MSYS2 (MinGW64):

    ```bash
    pacman -S mingw-w64-x86_64-arm-none-eabi-gcc mingw-w64-x86_64-arm-none-eabi-gdb
    ```

  * For Linux:

    ```bash
    sudo apt install gcc-arm-none-eabi gdb-arm-none-eabi
    ```
  
* [CMake](https://cmake.org/download/)
  * For Windows MSYS2 (MinGW64):

    ```bash
    pacman -S mingw-w64-x86_64-cmake
    ```

  * For Linux:

    ```bash
    sudo apt install cmake
    ```

* **Optional** for further development: [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx)

### Building

```bash
# Clone the repo and navigate into it 
git clone https://github.com/chieftain0/CharlieDeck32.git
cd CharlieDeck32

# Create a build directory and navigate into it 
mkdir build
cd build

# Create a separate Debug and Release build directories 
mkdir Debug & mkdir Release

cd Debug
# For Windows with MinGW:
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ../.. 
# For Linux:
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../.. 
# Build Debug build
mingw32-make

# Leave the Debug build directory 
cd ..

cd Release
# For Windows with MinGW:
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ../..
# For Linux:
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../..
# Build Release build
mingw32-make

# Leave the build directory 
cd ../..
```

### Executable

The build commands will produce a `CharlieDeck32.elf` file in the `CharlieDeck32/bin/Release` and `CharlieDeck32/bin/Debug` directories.

```bash
binwalk -e bin/Release/CharlieDeck32.elf
```

```bash
binwalk -e bin/Debug/CharlieDeck32.elf
```

### Flashing

* Connect your SWD programmer (ST-Link, etc.)
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

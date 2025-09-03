# CharlieDeck32

![Build](https://github.com/chieftain0/CharlieDeck32/actions/workflows/firmware-build.yml/badge.svg)

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

* **Optional**: [MSYS2](https://www.msys2.org/)

* Compile toolchains: [MinGW-W64](https://github.com/niXman/mingw-builds-binaries/releases) and [Ninja](https://github.com/ninja-build/ninja/releases)

  * For Windows MSYS2 (MinGW64):

    ```bash
    pacman -S mingw-w64-x86_64-gcc 
    pacman -S mingw-w64-x86_64-gdb
    pacman -S mingw-w64-x86_64-ninja
    ```

  * For Linux:

    ```bash
    sudo apt install build-essential
    sudo apt install ninja-build
    ```

* [STM32CubeCLT](https://www.st.com/en/development-tools/STM32CubeCLT)

  * Contains the `arm-none-eabi-gcc` and `arm-none-eabi-g++` compilers which can be installed separately (see below). Nevertheless, STM32CubeCLT is strongly recommended.
  * For Windows MSYS2 (MinGW64):

    ```bash
    pacman -S mingw-w64-x86_64-arm-none-eabi-gcc
    pacman -S mingw-w64-x86_64-arm-none-eabi-gdb
    ```

  * For Linux:

    ```bash
    sudo apt install gcc-arm-none-eabi
    sudo apt install gdb-arm-none-eabi
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

* Clone the repo and navigate into it

  ```bash
  git clone https://github.com/chieftain0/CharlieDeck32.git
  cd CharlieDeck32
  ```

* Create a build directory and navigate into it

  ```bash
  mkdir build & cd build
  ```

* Create separate Debug and Release build directories

  ```bash
  mkdir Debug & mkdir Release
  ```

* Navigate into the Debug build directory and build the project

  ```bash
  cd Debug

  # Configure the project
  cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug ../.. 

  # Build the project
  ninja
  ```

* Leave the Debug build directory

  ```bash
  cd ..
  ```

* Navigate into the Release build directory and build the project

  ```bash
  cd Release

  # Configure the project
  cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release ../..

  # Build the project
  ninja

  # Leave the build directory 
  cd ../..
  ```

### Executable

The build commands will produce a `CharlieDeck32.elf` file in the `CharlieDeck32/bin/Debug` and `CharlieDeck32/bin/Release` directories.

```bash
arm-none-eabi-objdump -f bin/Debug/CharlieDeck32.elf
```

```bash
arm-none-eabi-objdump -f bin/Release/CharlieDeck32.elf
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

* Make LED display function non-blocking.  
* Program the Tetris game.

## License

This project is licensed under the [**GPL-3.0** license](LICENSE).

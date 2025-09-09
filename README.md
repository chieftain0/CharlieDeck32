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

DIAGRAM HERE

## Software & Build Instructions

### Prerequisites

* [Git](https://git-scm.com/downloads)

* **Optional**: [MSYS2](https://www.msys2.org/)

* Compile toolchains: [MinGW-W64](https://github.com/niXman/mingw-builds-binaries/releases) and [Ninja](https://github.com/ninja-build/ninja/releases)

  * For Windows MSYS2 (MinGW64):

    ```bash
    pacman -S --needed --noconfirm mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb mingw-w64-x86_64-ninja
    ```

  * For Linux:

    ```bash
    sudo apt install build-essential ninja-build -y
    ```

* [ARM None EABI Toolchain](https://developer.arm.com/downloads/-/gnu-rm)

  * [STM32CubeCLT](https://www.st.com/en/development-tools/stm32cubeclt.html) contains `arm-none-eabi-gcc` and `arm-none-eabi-gdb` and is strongly recommended for further development.
  
  * For Windows MSYS2 (MinGW64):

    ```bash
    pacman -S --needed --noconfirm mingw-w64-x86_64-arm-none-eabi-gcc mingw-w64-x86_64-arm-none-eabi-gdb
    ```

  * For Linux:

    ```bash
    sudo apt install gcc-arm-none-eabi gdb-arm-none-eabi -y
    ```
  
* [CMake](https://cmake.org/download/)
  * For Windows MSYS2 (MinGW64):

    ```bash
    pacman -S --needed --noconfirm mingw-w64-x86_64-cmake
    ```

  * For Linux:

    ```bash
    sudo apt install cmake -y
    ```

* **Optional** for further development: [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx)

### Building

* Clone the repo and navigate into it

  ```bash
  git clone https://github.com/chieftain0/CharlieDeck32.git
  cd CharlieDeck32
  ```

* Build the Debug version of the project

  ```bash
  # Configure build files
  cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -B build/Debug

  # Build the project
  ninja -C build/Debug
  ```

* Build the Release version of the project

  ```bash
  # Configure the project
  cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release -B build/Release

  # Build the project
  ninja -C build/Release
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
  * FreeRTOS?
* Program the Tetris game.

## License

This project is licensed under the [**GPL-3.0** license](LICENSE).

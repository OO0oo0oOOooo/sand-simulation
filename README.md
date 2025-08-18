# Falling Sand Simulation

[![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B)
[![CMake](https://img.shields.io/badge/Build-CMake-brightgreen.svg)](https://cmake.org/)

A simple, 2D falling sand simulation game implemented in my custom C/C++ Game Engine.

---

## 📖 Table of Contents

* [✨ Features](#-features)
* [🚀 How to Build](#-how-to-build)
	* [TLDR](#tldr)
	* [Steps](#steps)
* [🐧 Platform Notes](#-platform-notes)
	* [Linux](#linux)
	* [Windows](#windows)

---

## ✨ Features

* **Simple 2D Sandbox:** A simple sand toy with multiple particle types and fun interactions.
* **Built from scratch:** Built using my custom game engine that only uses a few librarys.
* **Cross-Platform (Planned/Partial):** Designed with portability in mind.

*(GIF or screenshot here)*
---

## 🚀 How to Build

### FOR LINUX

You will need the dev packages for x11 and Wayland for GLFW to link to see [🐧 Platform Notes](#linux) for more info

### TLDR
```bash
git clone [https://github.com/OO0oo0oOOooo/sand-simulation.git](https://github.com/OO0oo0oOOooo/sand-simulation.git)
cd sand-simulation
mkdir build
cd build
cmake ..
make
..
./sand-simulation
```

### Steps

Follow these steps to compile the source code:


1.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/OO0oo0oOOooo/sand-simulation.git](https://github.com/OO0oo0oOOooo/sand-simulation.git)
    cd sand-simulation
    ```

2.  **Create and Enter Build Directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Generate Makefile/Project Files with CMake:**
    ```bash
    cmake ..
    ```

4.  **Compile the Project:**
    ```bash
    make
    ```

---

### FOR WINDOWS

I haven't tested or documented the build process on Windows yet. However, it *should* work with popular compilers like **MSVC (Visual Studio)** or **MinGW**. I think double clicking the executable will not work unless its in the same folder as 'resources' and will be fixed soon. I recommend running the executable as instructed in [🎮 How to Run](#-how-to-run)

## 🐧 Platform Notes

### Linux

For successful compilation on Linux, you will need the development packages for X11 and Wayland for GLFW to link correctly and support both window managers.

Common packages include:
* `mesa-libGL-devel`
* `libxkbcommon-devel`

Wayland
* `wayland-protocols`
* `wayland-devel`

X11
* `libX11-devel`
* `libXrandr-devel`
* `libXi-devel`
* `libXcursor-devel`
* `libXrender-devel`
* `libXinerama-devel`

*(Package names may vary slightly depending on your specific distribution.)*

### Windows

I haven't tested or documented the build process on Windows yet and will update this when i do.

*If you encounter issues, please open an issue on the GitHub repository!*

---

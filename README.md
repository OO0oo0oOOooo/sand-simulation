# Falling Sand Simulation

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B)
[![CMake](https://img.shields.io/badge/Build-CMake-brightgreen.svg)](https://cmake.org/)

A simple, lightweight 2D falling sand simulation game implemented in C++. Experience the fascinating behavior of various elements as they interact and fall, creating intricate patterns.

---

## 📖 Table of Contents

* [✨ Features](#-features)
* [🚀 How to Build](#-how-to-build)
	* [TLDR](#tldr)
	* [Steps](#steps)
* [🎮 How to Run](#-how-to-run)
* [🐧 Platform Notes](#-platform-notes)
	* [Linux](#linux)
	* [Windows](#windows)
* [📚 Third-Party Libraries](#-third-party-libraries)

---

## ✨ Features

* **Simple 2D Sandbox:** A simple sand toy with multiple particle types and fun interactions.
* **Built from scratch:** Rendering and all systems built from scratch with the help of only a few librarys.
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
./build/sand-simulation    
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

I haven't tested or documented the build process on Windows yet. However, it *should* work with popular compilers like **MSVC (Visual Studio)** or **MinGW**. I think double clicking the executable will not work unless its in the same folder as 'resources' and will be fixed soon. I recommend running the executable as instructed in [🎮 How to Run](#-how-to-build)

## 🎮 How to Run

**Important:** The executable *must* be run from the **root of the project directory**. Running it from the `build` folder will cause resource loading failures (e.g., images, shaders) because the relative paths will be incorrect.

1.  **Navigate to the Project Root:**
    If you are still in the `build` directory after compilation, navigate back to the main project directory:

    ```bash
    cd ..
    ```

2.  **Execute the Simulation:**
    Run the compiled executable. The name of the executable might vary slightly depending on your platform and CMake configuration, but it's typically `sand-simulation`.

    ```bash
    ./build/sand-simulation
    ```
    *On Windows, it might be `.\build\Debug\sand-simulation.exe` or `.\build\Release\sand-simulation.exe` depending on your build configuration.*

---

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

## 📚 Third-Party Libraries

All necessary external libraries are included directly within the project's `lib/` directory or managed by CMake's `FetchContent`.

The key libraries used are:

* [**GLFW**](https://www.glfw.org/): A multi-platform library for OpenGL, OpenGL ES, and Vulkan development, providing a simple API for creating windows, contexts and surfaces, receiving input and events.
* [**Glad**](https://glad.dav1d.de/): A multi-language Vulkan/GL/GLES/EGL/GLX/WGL loader-generator. It allows you to load OpenGL functions dynamically.
* [**GLM**](https://glm.g-truc.net/): OpenGL Mathematics, a header-only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.
* [**stb_image**](https://github.com/nothings/stb/blob/master/stb_image.h): A single-file public domain library for loading images.
* [**ImGui**](https://github.com/ocornut/imgui): Dear ImGui is a graphical user interface library for C++.

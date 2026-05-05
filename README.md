# 🏓 Rogue Pong

A roguelike twist on Pong where every run evolves through modifiers, cards, and chaotic mechanics.

Built using **C++**, **SDL3**, and **CMake**.

---

# 📑 Index

* [🎮 Concept](#-concept)
* [🔥 Goal](#-goal)
* [🚀 Features](#-features)
* [⚙️ Setup & Installation](#️-setup--installation)

  * [🐧 Linux Setup](#-linux-recommended--simple)
  * [🪟 Windows Setup](#-windows-using-msys2--mingw)
* [🧠 Notes](#-notes)
* [📁 Project Structure](#-project-structure)
* [🚫 .gitignore](#-gitignore-important)

---

## 🎮 Concept

Rogue Pong transforms classic Pong into a **run-based progression game**.

Each match changes gameplay through:

* 🃏 Modifiers (cards / effects)
* ⚡ Dynamic physics changes
* 🎯 Increasing difficulty

---

### 🔁 Core Gameplay Loop

```text
Play Match → Earn Reward → Choose Modifier → Game Evolves → Repeat
```

---

### 🧠 Gameplay Ideas

* Ball speed, size, and behavior can change mid-run
* Paddle abilities evolve (wider, faster, special effects)
* Multi-ball, curve shots, or chaotic physics
* Risk vs reward modifiers

---

## 🔥 Goal

Survive increasingly difficult rallies while building a powerful (or unstable) setup.

---

## 🚀 Features

* Cross-platform (Windows + Linux)
* Uses SDL3 for graphics and input
* Clean CMake-based build system

---

# ⚙️ Setup & Installation

## 🐧 Linux (Recommended / Simple)

👉 Jump back: [Index](#-index)

Linux already provides everything needed.

### Install dependencies:

```bash
sudo apt update
sudo apt install build-essential cmake libsdl3-dev
```

---

### Build the project:

```bash
git clone <your-repo-url>
cd ping-pong

cmake -S . -B build
cmake --build build
```

---

### Run:

```bash
./build/PingPong
```

---

## 🪟 Windows (Using MSYS2 + MinGW)

👉 Jump back: [Index](#-index)

Windows requires a Unix-like environment to match Linux workflow.

### 1. Install MSYS2

Download and install **MSYS2**

---

### 2. Open terminal

```text
MSYS2 MinGW64
```

---

### 3. Install dependencies

```bash
pacman -Syu
# restart terminal if asked, then run again:
pacman -Syu

pacman -S mingw-w64-x86_64-gcc \
           mingw-w64-x86_64-cmake \
           mingw-w64-x86_64-sdl3
```

---

### 4. Build project

```bash
cd /c/Users/<your-username>/path/to/ping-pong

cmake -S . -B build
cmake --build build
```

---

### 5. Run

```bash
./build/PingPong.exe
```

---

### ⚠️ If SDL3.dll error occurs

```bash
cp /mingw64/bin/SDL3.dll build/
```

---

## 🧠 Notes

👉 Jump back: [Index](#-index)

The project uses:

```cmake
find_package(SDL3 REQUIRED)
```

This allows automatic detection of SDL3 on both:

* Linux (`apt`)
* Windows (`MSYS2`)

No changes to `CMakeLists.txt` are required.

---

## 📁 Project Structure

```text
ping-pong/
├── src/
│   └── main.cpp
├── CMakeLists.txt
├── build/   (generated, not tracked)
```

---

## 🚫 .gitignore (important)

```text
build/
*.exe
*.dll
```

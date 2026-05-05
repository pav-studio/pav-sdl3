# 🏓 Ping Pong (SDL3 + CMake)

A simple cross-platform Ping Pong project built using **C++**, **SDL3**, and **CMake**.

---

## 🚀 Features

* Cross-platform (Windows + Linux)
* Uses SDL3 for graphics and input
* Clean CMake-based build system

---

# ⚙️ Setup & Installation

## 🐧 Linux (Recommended / Simple)

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

Windows requires a Unix-like environment to match Linux workflow.

### 1. Install MSYS2

Download and install **MSYS2**.

---

### 2. Open terminal

Use:

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

# 🧠 Notes

* The project uses:

```cmake
find_package(SDL3 REQUIRED)
```

* This allows automatic detection of SDL3 on both:

  * Linux (`apt`)
  * Windows (`MSYS2`)

* No changes to `CMakeLists.txt` are required.

---

# 📁 Project Structure

```text
ping-pong/
├── src/
│   └── main.cpp
├── CMakeLists.txt
├── build/   (generated, not tracked)
```

---

# 🚫 .gitignore (important)

Make sure to ignore build artifacts:

```text
build/
*.exe
*.dll
```



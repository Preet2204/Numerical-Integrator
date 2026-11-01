# Numerical Integrator

A small C++ project for learning numerical integration methods and GUI programming with [raylib](https://www.raylib.com/).

> **Note on versions:** This project started as a CLI program (`main.cpp`). The current, latest version is the GUI program in `integrator.cpp`, built with raylib and raygui. `main.cpp` is kept as the legacy command-line version.

## What it does

Computes the definite integral of a function of `x` over an interval `[a, b]` using three numerical methods:

1. **Trapezoidal Rule** — works for any number of intervals.
2. **Simpson's 1/3 Rule** — requires the number of intervals to be a multiple of 2.
3. **Simpson's 3/8 Rule** — requires the number of intervals to be a multiple of 3.

The GUI version lets you type in your own function (e.g. `x*x + 3*x + 2`, `sin(5*x)/2 + 1`), set the lower and upper limits and the number of intervals, then click **Integrate** to see all applicable results side by side. Invalid inputs are highlighted with error messages, and **Reset** restores the default values.

## Why this project exists

This was built for learning purposes — to understand how numerical integration methods work under the hood, and to get hands-on with raylib/raygui for building a desktop GUI in C++. It is not intended to be a production-grade numerical library.

## Tech stack

- **Language:** C++ (C++17)
- **GUI:** raylib 5.5 + raygui (fetched automatically by CMake)
- **Expression parsing:** [tinyexpr](https://github.com/codeplea/tinyexpr) (vendored, Zlib license) — parses the user-typed function at runtime
- **Build system:** CMake
- **Font:** `resources/C059-Roman.otf`

## Project structure

```
Numerical-Integrator/
├── integrator.cpp    # Latest GUI version (raylib + raygui + tinyexpr)
├── main.cpp          # Legacy CLI version (hardcoded functions, error table)
├── tinyexpr.c        # Vendored expression parser
├── tinyexpr.h
├── CMakeLists.txt    # CMake build (fetches raylib & raygui)
├── resources/
│   └── C059-Roman.otf
├── LICENSE           # MIT
└── README.md
```

## Building

You need a C++17 compiler and CMake. raylib and raygui are downloaded and built automatically via CMake's `FetchContent`, so you don't need to install them beforehand.

```bash
# Clone or enter the project folder
cd Numerical-Integrator

# Configure and build
mkdir -p build && cd build
cmake ..
cmake --build .   # or: make
```

The `resources/` folder is copied into the build directory automatically so the font loads at runtime.

Run the program:

```bash
./integrator
```

## Building on Windows

The same CMake setup works on Windows. You will need:

- **CMake** (3.14 or newer)
- **A C++ compiler**: MSVC (via Visual Studio Build Tools), MinGW-w64, or Clang
- **Git** (required by CMake's FetchContent to download raylib and raygui)
- An internet connection (for FetchContent to download dependencies)

### Option A: Visual Studio / MSVC (Recommended)

Open a "Developer Command Prompt for VS" or "x64 Native Tools Command Prompt":

```powershell
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

This produces `build/Release/integrator.exe`. Run it from the `build/` folder so it can find the copied `resources/` font:

```powershell
cd build
.\Release\integrator.exe
```

### Option B: MinGW-w64

```powershell
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

This produces `build/integrator.exe`. Run it from the `build/` folder:

```powershell
cd build
.\integrator.exe
```

### Notes

- raylib and raygui are downloaded and compiled automatically by CMake's `FetchContent`, so you don't need to install them manually.
- The `resources/` folder is copied into `build/` at configure time, so run the executable from the `build/` directory (or copy `resources/` next to the `.exe`) so the font loads correctly.
- If you get a missing DLL error at runtime, you may need the Microsoft Visual C++ Redistributable (for MSVC) or MinGW's `bin` folder in your PATH (for MinGW).

## How to use (GUI version)

1. Run `./integrator`.
2. Type a function of `x` in the **Enter function of x** field (default: `x*x + 3*x + 2`). Examples:
   - `x*x + 3*x + 2`
   - `sin(5*x)/2 + 1`
   - `3*cos(2*x) + 2`
   - `2*exp(3*x)`
3. Enter the **Lower Limit**, **Upper Limit**, and **Intervals**.
4. Click **Integrate**.
5. Results for each applicable method appear on screen. Simpson's methods show "Invalid intervals" when the interval count doesn't meet their divisibility requirement.
6. Click **Reset** to restore default values.

### Input validation

- All fields must be filled in.
- Limits and intervals must be numeric.
- Lower limit must be ≤ upper limit.
- Intervals must be greater than 0.
- The function expression must be parseable by tinyexpr.

## Legacy CLI version (`main.cpp`)

The original version runs in the terminal. It offers four predefined functions, computes each applicable method, compares against the exact integral, prints absolute errors, and reports the most accurate method. It is kept for reference; `integrator.cpp` is the active version.

## License

MIT License. See `LICENSE` for details.

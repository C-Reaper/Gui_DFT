# Project README

## Overview
This project is a C application for visualizing Discrete Fourier Transform (DFT) using a graphical user interface. It includes features such as loading data, performing DFT, and displaying the results graphically.

## Features
- **Data Loading**: Load data from a text file.
- **Discrete Fourier Transform (DFT)**: Compute the DFT of the loaded data.
- **Graphical Display**: Visualize the original data and its DFT coefficients.
- **User Interface**: Interact with the application through a graphical interface.

## Project Structure
- **build/**: Contains executable files produced by compiling Main.c.
- **src/**:
  - **Main.c**: Entry point of the program.
  - **DFT.h**, **DFT.c**: Header and implementation for DFT calculations.
  - **GUI.h**, **GUI.c**: Header and implementation for graphical user interface.

### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- Libraries needed in specific projects:
  - X11: For cross-platform GUI window management on Linux.
  - WINAPI: For Windows-specific GUI functionalities.
  - ALSA: For audio processing features.

## Build & Run
### Building the Project

To build the project, navigate to the project directory and use the appropriate Makefile for your operating system:

#### Linux
```bash
cd <Project>
make -f Makefile.linux all
```

#### Windows
```bash
cd <Project>
make -f Makefile.windows all
```

#### Wine (Linux Cross Compile for Windows)
```bash
cd <Project>
make -f Makefile.wine all
```

#### WebAssembly (Emscripten)
```bash
cd <Project>
make -f Makefile.web all
```

### Executing the Program

To run the compiled program, use:
```bash
make -f Makefile.(os) exe
```
Replace `(os)` with `linux`, `windows`, or `wine` as appropriate.

### Clean Rebuild
To perform a clean rebuild of the project:
```bash
make -f Makefile.(os) clean
make -f Makefile.(os) all
```

### Build Options
- **Build Output**: `make -f Makefile.(os) all`
- **Build and Execute**: `make -f Makefile.(os) do`
- **Clean Artifacts**: `make -f Makefile.(os) clean`
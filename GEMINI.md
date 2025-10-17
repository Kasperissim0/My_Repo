# Gemini Code Assistant Context

This document provides context for the Gemini Code Assistant to understand the structure and conventions of this C++ learning project.

## Project Overview

This is a personal C++ learning repository containing a collection of individual source files rather than a single, unified project. The files are organized into directories based on their status and purpose (`Active`, `Archive`, `upload`).

The projects range from simple command-line tools to graphical applications using the [SFML](https://www.sfml-dev.org/) library.

### Key Technologies
*   **Language:** C++ (using C++17 and C++20 standards)
*   **Compiler:** Clang++
*   **Graphics:** SFML (Simple and Fast Multimedia Library)
*   **Editor:** Visual Studio Code

## Building and Running

The project is configured to build and run individual files using VS Code tasks.

### Building a File

To compile a C++ file (e.g., `my_file.cpp`), the following command is used:

```bash
clang++ -fcolor-diagnostics -fansi-escape-codes -std=c++20 -g my_file.cpp -o Build/my_file -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
```

**Explanation:**

*   `clang++`: The C++ compiler.
*   `-std=c++20`: Specifies the C++20 standard.
*   `-g`: Includes debugging information.
*   `my_file.cpp`: The input source file.
*   `-o Build/my_file`: The output executable, placed in the `Build` directory.
*   `-I...`, `-L...`, `-l...`: Flags for linking the SFML libraries.

### Running an Executable

Once a file is built, the executable can be run from the `Build` directory:

```bash
./Build/my_file
```

## Development Conventions

### Code Formatting

Code formatting is enforced by the `.clang-format` file. Key style guidelines include:

*   **Indent Width:** 2 spaces
*   **Tabs:** Never used
*   **Braces:** Attached (`BreakBeforeBraces: Attach`)
*   **Spacing:** Space before parentheses (`SpaceBeforeParens: Always`)

### Directory Structure

*   `.vscode/`: Contains VS Code settings, build tasks, and launch configurations.
*   `Active/`: For projects currently being worked on.
*   `Archive/`: For completed or inactive projects.
*   `Build/`: The output directory for compiled executables.
*   `upload/`: Contains files for specific tasks.

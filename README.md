# OBJ Mesh Analyzer

A beginner-friendly C++20 learning project that loads a Wavefront OBJ mesh file and prints basic information about it.

## What It Does

- Loads `assets/cube.obj`
- Counts shapes
- Counts vertices
- Counts triangles
- Calculates an axis-aligned bounding box
- Prints the results to the console

## Project Structure

```text
obj-reader/
├── CMakeLists.txt
├── app/
│   └── main.cpp
└── assets/
    └── cube.obj
```

## Libraries Used

- [fmt](https://github.com/fmtlib/fmt) for printing
- [glm](https://github.com/g-truc/glm) for 3D vector math
- [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader) for loading OBJ files

The libraries are downloaded automatically by CMake using `FetchContent`.

## How To Run In CLion

1. Open this folder in CLion.
2. Wait for CMake to finish loading the project.
3. Select the `mesh_analyzer` run target.
4. Click Run.

Expected output:

```text
Mesh analysis for assets/cube.obj
Shapes: 1
Vertices: 8
Triangles: 12
Bounds min: (-0.500, -0.500, -0.500)
Bounds max: (0.500, 0.500, 0.500)
Bounds center: (0.000, 0.000, 0.000)
Bounds size: (1.000, 1.000, 1.000)
```

## Project Name And Description

**Name:** OBJ Mesh Analyzer

**Description:** A small C++20 learning project for practicing basic mesh loading, vertex counting, bounding box math, and console output.

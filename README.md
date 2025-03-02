# Rotating Cube Animation

This C++ project creates an animated 3D cube that rotates and floats vertically within the console window. The cube is rendered using ASCII characters and a simple perspective projection, giving the illusion of depth and motion.

---

## Features

- **3D Rendering in Console:**  
  Draws a rotating cube using ASCII characters on a fixed-size console grid.

- **Perspective Projection:**  
  Uses a basic perspective projection to simulate depth.

- **Rotation on Multiple Axes:**  
  The cube rotates around the X, Y, and Z axes for a dynamic visual effect.

- **Vertical Floating Effect:**  
  Applies a periodic vertical offset to simulate a floating motion.

- **DDA Line Drawing Algorithm:**  
  Implements the Digital Differential Analyzer (DDA) algorithm for drawing straight lines between vertices.

---

## Project Structure

- **`main()` Function:**  
  Contains the main game loop that continuously updates the cube’s rotation angles and vertical offset, then redraws the cube.

- **`drawCube()` Function:**  
  Computes the 3D rotations, applies perspective projection, and renders the cube’s edges to an off-screen buffer, which is then printed to the console.

- **Utility Functions:**  
  - `drawLine()`: Draws lines between projected vertices using the DDA algorithm.
  - Other helper functions handle rotations, projection, and buffer management.

---

## Compiling the Project

```bash
g++ -std=c++11 -o rotating_cube main.cpp

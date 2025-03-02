#include <iostream>
#include <cmath>
#include <cstring>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

const int width = 80;   // Console width
const int height = 40;  // Console height
const float zDistance = 5.0f; // Depth factor (for perspective)
const float scale = 20.0f;    // Scale for projection

struct Vertex {
    float x, y, z;
};

struct Edge {
    int a, b;
};

// Draws a line between two points (using DDA algorithm)
void drawLine(int x0, int y0, int x1, int y1, char ch, char* buffer) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = max(abs(dx), abs(dy));
    if (steps == 0) {
        if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)
            buffer[y0 * width + x0] = ch;
        return;
    }
    float xIncrement = dx / static_cast<float>(steps);
    float yIncrement = dy / static_cast<float>(steps);
    float x = x0, y = y0;
    for (int i = 0; i <= steps; i++) {
        int xi = round(x);
        int yi = round(y);
        if (xi >= 0 && xi < width && yi >= 0 && yi < height)
            buffer[yi * width + xi] = ch;
        x += xIncrement;
        y += yIncrement;
    }
}

void drawCube(float angleX, float angleY, float angleZ, float floatOffset) {
    char buffer[width * height];
    memset(buffer, ' ', sizeof(buffer));

    // Define the cube's 8 vertices
    Vertex cube[8] = {
        {-1, -1, -1}, { 1, -1, -1}, { 1,  1, -1}, {-1,  1, -1},
        {-1, -1,  1}, { 1, -1,  1}, { 1,  1,  1}, {-1,  1,  1}
    };

    // Define edges (pairs of vertex indices)
    vector<Edge> edges = {
        {0,1}, {1,2}, {2,3}, {3,0}, // Front face
        {4,5}, {5,6}, {6,7}, {7,4}, // Back face
        {0,4}, {1,5}, {2,6}, {3,7}  // Connecting edges
    };

    // Array to hold projected 2D coordinates
    pair<int, int> proj[8];

    // Apply rotations and projection for each vertex
    for (int i = 0; i < 8; i++) {
        float x = cube[i].x;
        float y = cube[i].y;
        float z = cube[i].z;

        // Rotate around X axis
        float tempY = y * cos(angleX) - z * sin(angleX);
        float tempZ = y * sin(angleX) + z * cos(angleX);
        y = tempY;
        z = tempZ;

        // Rotate around Y axis
        float tempX = x * cos(angleY) + z * sin(angleY);
        tempZ = -x * sin(angleY) + z * cos(angleY);
        x = tempX;
        z = tempZ;

        // Rotate around Z axis
        tempX = x * cos(angleZ) - y * sin(angleZ);
        tempY = x * sin(angleZ) + y * cos(angleZ);
        x = tempX;
        y = tempY;

        // Apply vertical (floating) offset
        y += floatOffset;

        // Perspective projection
        float zFactor = 1.0f / (z + zDistance);
        int screenX = static_cast<int>(width / 2 + scale * x * zFactor);
        int screenY = static_cast<int>(height / 2 - scale * y * zFactor);
        proj[i] = {screenX, screenY};
    }

    // Draw the cube edges
    for (const Edge &edge : edges) {
        drawLine(proj[edge.a].first, proj[edge.a].second,
                 proj[edge.b].first, proj[edge.b].second, '#', buffer);
    }

    // Output the buffer to the console
    cout << "\x1b[H"; // Move cursor to top-left
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            cout << buffer[i * width + j];
        cout << "\n";
    }
}

int main() {
    float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;
    float floatOffset = 0.0f;
    int floatDirection = 1;

    cout << "\x1b[2J"; // Clear screen

    while (true) {
        drawCube(angleX, angleY, angleZ, floatOffset);
        angleX += 0.05f;
        angleY += 0.03f;
        angleZ += 0.02f;
        floatOffset += floatDirection * 0.05f;
        if (floatOffset > 1.0f || floatOffset < -1.0f)
            floatDirection *= -1;
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    return 0;
}

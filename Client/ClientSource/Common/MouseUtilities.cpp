/*
 * MouseUtilities.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseUtilities.hpp"
#include "ClientCore/Graphics/Graphics.hpp"

namespace JoD {
PointF GetMousePosition() {
// Declare variables to store mouse coordinates in pixels.
    double xPos;
    double yPos;
// Use GLFW to get current mouse coordinates.
    glfwGetCursorPos(_<Graphics>().GetWindow(), &xPos, &yPos);
// Get canvas size.
    const auto canvasSize = GetCanvasSize();
// And use it to convert pixel coordinates to fractal coordinates.
    const auto mousePosition = PointF{
        static_cast<float>(xPos) / canvasSize.w,
        static_cast<float>(yPos) / canvasSize.h};
    return mousePosition;
}
}
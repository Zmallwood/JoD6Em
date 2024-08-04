/*
 * MouseUtilities.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseUtilities.hpp"
#include "ClientCore/Graphics/Graphics.hpp"

namespace JoD {
    PointF GetMousePosition() {
        double xPos, yPos; // Declare variables to store mouse coordinates in pixels.
        // Use GLFW to get current mouse coordinates.
        glfwGetCursorPos(_<Graphics>().m_window, &xPos, &yPos);
        auto canvasSize = GetCanvasSize(); // Get canvas size.
        // And use it to convert pixel coordinates to fractal coordinates.
        auto mousePosition = PointF{
            static_cast<float>(xPos) / canvasSize.w,
            static_cast<float>(yPos) / canvasSize.h};
        return mousePosition;
    }
}
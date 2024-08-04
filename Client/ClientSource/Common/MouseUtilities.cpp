/*
 * MouseUtilities.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseUtilities.hpp"
#include "ClientCore/Graphics/Graphics.hpp"

namespace JoD {
    PointF GetMousePosition() {
        double xpos, ypos; // Declare variables to store mouse coordinates in pixels.
        // Use GLFW to get current mouse coordinates.
        glfwGetCursorPos(_<Graphics>().m_window, &xpos, &ypos);
        auto canvas_size = GetCanvasSize(); // Get canvas size.
        // And use it to convert pixel coordinates to fractal coordinates.
        auto mouse_position = PointF{
            static_cast<float>(xpos) / canvas_size.w,
            static_cast<float>(ypos) / canvas_size.h};
        return mouse_position;
    }
}
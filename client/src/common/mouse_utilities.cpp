/*
 * mouse_utilities.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "mouse_utilities.h"
#include "client_core/graphics/graphics.h"

namespace jod {
    pointf
    get_mouse_position(){
        double xpos, ypos; // Declare variables to store mouse coordinates in pixels.
        // Use GLFW to get current mouse coordinates.
        glfwGetCursorPos(_<graphics>().m_window, &xpos, &ypos);
        auto canvasSize = get_canvas_size(); // Get canvas size.
        // And use it to convert pixel coordinates to fractal coordinates.
        auto mousePosition = pointf{
            static_cast<float>(xpos) / canvasSize.w,
            static_cast<float>(ypos) / canvasSize.h};
        return mousePosition;
    }
}
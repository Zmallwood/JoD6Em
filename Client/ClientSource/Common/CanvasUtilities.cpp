/*
 * CanvasUtilities.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "CanvasUtilities.h"
#include "ClientCore/Graphics/Graphics.h"

namespace JoD {
    Size GetCanvasSize()      {
        int w, h; // To store dimensions in pixels.
        // Use GLFW to get canvas size.
        glfwGetWindowSize(_<Graphics>().m_window, &w, &h);
        return {w, h};
    }
    
    float GetAspectRatio()       {
        auto canvas_size = GetCanvasSize(); // Get canvas dimensions.
        // And calculate the ratio between them.
        auto aspect_ratio = static_cast<float>(canvas_size.w) / canvas_size.h;
        return aspect_ratio;
    }
    
    float ConvertWidthToHeight(float width)       {
        // Use aspect ratio to convert from width to corresponding height.
        return width * GetAspectRatio();
    }

    float ConvertHeightToWidth(float height) {
        return height / GetAspectRatio();
    }
    
    SDL_Color ToSDLColor(ColorF color)           {
        return {static_cast<unsigned char>(color.r * 255),
                static_cast<unsigned char>(color.g * 255),
                static_cast<unsigned char>(color.b * 255),
                static_cast<unsigned char>(color.a * 255)};
    }
}
/*
 * CanvasUtilities.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "CanvasUtilities.hpp"
#include "ClientCore/Graphics/Graphics.hpp"

namespace JoD {
    Size GetCanvasSize()      {
        int width, height; // To store dimensions in pixels.
        // Use GLFW to get canvas size.
        glfwGetWindowSize(_<Graphics>().m_window, &width, &height);
        return {width, height};
    }
    
    float GetAspectRatio()       {
        auto canvasSize = GetCanvasSize(); // Get canvas dimensions.
        // And calculate the ratio between them.
        auto aspectRatio = static_cast<float>(canvasSize.w) / canvasSize.h;
        return aspectRatio;
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
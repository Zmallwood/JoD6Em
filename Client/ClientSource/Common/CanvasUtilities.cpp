/*
 * CanvasUtilities.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "CanvasUtilities.hpp"
#include "ClientCore/Graphics/Graphics.hpp"

namespace JoD {
    
    Size GetCanvasSize() {
        
        // To store dimensions in pixels.
        int width;
        int height;
        
        // Use GLFW to get canvas size.
        glfwGetWindowSize(_<Graphics>().GetWindow(), &width, &height);
        
        return {width, height};
    }
    
    float GetAspectRatio() {
        
        // Get canvas dimensions.
        const auto canvasSize = GetCanvasSize();
        
        // And calculate the ratio between them.
        const auto aspectRatio = static_cast<float>(canvasSize.w) / canvasSize.h;
        
        return aspectRatio;
    }
    
    float ConvertWidthToHeight(float width) {
        
        // Use aspect ratio to convert from width to corresponding height.
        return width * GetAspectRatio();
    }
    
    float ConvertHeightToWidth(float height) {
        
        // Use aspect ratio to convert from height to corresponding width.
        return height / GetAspectRatio();
    }
    
    SDL_Color ToSDLColor(ColorF color) {
        
        // Convert color components individually.
        return {static_cast<unsigned char>(color.r * 255),
                static_cast<unsigned char>(color.g * 255),
                static_cast<unsigned char>(color.b * 255),
                static_cast<unsigned char>(color.a * 255)};
    }
}
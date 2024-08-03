/*
 * CanvasUtilities.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "CanvasUtilities.h"
#include "ClientCore/Graphics/Graphics.h"

namespace jod {
    size get_canvas_size()      {
        int w, h; // To store dimensions in pixels.
        // Use GLFW to get canvas size.
        glfwGetWindowSize(_<graphics>().m_window, &w, &h);
        return {w, h};
    }
    
    float get_aspect_ratio()       {
        auto canvas_size = get_canvas_size(); // Get canvas dimensions.
        // And calculate the ratio between them.
        auto aspect_ratio = static_cast<float>(canvas_size.w) / canvas_size.h;
        return aspect_ratio;
    }
    
    float convert_width_to_height(float width)       {
        // Use aspect ratio to convert from width to corresponding height.
        return width * get_aspect_ratio();
    }
    
    float convert_height_to_width(float height)       {
        // Use aspect ratio to convert from height to corresponding width.
        return height / get_aspect_ratio();
    }
    
    SDL_Color to_sdl_color(colorf color)           {
        return {static_cast<unsigned char>(color.r * 255),
                static_cast<unsigned char>(color.g * 255),
                static_cast<unsigned char>(color.b * 255),
                static_cast<unsigned char>(color.a * 255)};
    }
}
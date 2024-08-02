// canvas_utilities.cpp
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
//

#include "canvas_utilities.h"
#include "client_core/graphics/graphics.h"

namespace jod {
    size
    get_canvas_size(){
        int w, h; // To store dimensions in pixels.
        // Use GLFW to get canvas size.
        glfwGetWindowSize(_<graphics>().m_window, &w, &h);
        return {w, h};
    }
    
    float
    get_aspect_ratio(){
        auto canvasSize = get_canvas_size(); // Get canvas dimensions.
        // And calculate the ratio between them.
        auto aspectRatio = static_cast<float>(canvasSize.w) / canvasSize.h;
        return aspectRatio;
    }
    
    float
    convert_width_to_height(float width){
        // Use aspect ratio to convert from width to corresponding height.
        return width * get_aspect_ratio();
    }
    
    float
    convert_height_to_width(float height){
        // Use aspect ratio to convert from height to corresponding width.
        return height / get_aspect_ratio();
    }
}
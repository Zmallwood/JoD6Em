/*
 * GLRectF.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Rectangle object with float dimensions, ment to represent a rectangle for OpenGLs
    /// default coordinate system.
    ///
    struct GLRectF {
        
        float x {0.0f}; ///< X coordinate in float type.
        
        float y {0.0f}; ///< Y coordinate in float type.
        
        float w {0.0f}; ///< Width in float type.
        
        float h {0.0f}; ///< Height in float type.
    };
}
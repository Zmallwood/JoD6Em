/*
 * RectF.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class GLRectF;

    /// @brief Rectangle object with float dimensions, ment to represent a rectangle in standard
    ///        screen coordinates, with 0,0 being in top left corner and 1,1 being in bottom right
    ///        corner.
    struct RectF {
        /// @brief Convert this objects values to format of OpenGLs default coordinate system.
        /// @return GLRectF Converted resulting object.
        GLRectF to_glrectf() const;
        
        float x = 0.0f; ///< X coordinate in float type.
        float y = 0.0f; ///< Y coordinate in float type.
        float w = 0.0f; ///< Width in float type.
        float h = 0.0f; ///< Height in float type.
    };
}
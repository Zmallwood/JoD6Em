/*
 * RectF.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RectF.hpp"
#include "GLRectF.hpp"

namespace JoD {
    GLRectF RectF::to_glrectf() const {
        // Do transformation to OpenGL canvas coordinates.
        return {x * 2 - 1.0f, 1.0f - y * 2, w * 2, h * 2};
    }
}
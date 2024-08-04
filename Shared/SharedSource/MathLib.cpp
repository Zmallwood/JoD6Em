/*
 * MathLib.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MathLib.h"

namespace JoD {
    GLRectF RectF::to_glrectf() const {
        // Do transformation to OpenGL canvas coordinates.
        return {x * 2 - 1.0f, 1.0f - y * 2, w * 2, h * 2};
    }
}
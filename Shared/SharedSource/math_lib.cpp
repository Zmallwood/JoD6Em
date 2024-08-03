/*
 * math_lib.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "math_lib.h"

namespace jod {
    glrectf rectf::to_glrectf() const {
        // Do transformation to OpenGL canvas coordinates.
        return {x * 2 - 1.0f, 1.0f - y * 2, w * 2, h * 2};
    }
}
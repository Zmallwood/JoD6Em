/*
 * RectF.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "BoxF.hpp"
#include "GLBoxF.hpp"

namespace JoD {
    
    GLBoxF BoxF::ToGLBoxF() const {
        
        // Do transformation to OpenGL canvas coordinates.
        return {x * 2 - 1.0f, 1.0f - y * 2, w * 2, h * 2};
    }
}
// Copyright (c) 2024 Andreas Åkerberg.

#include "MathLib.h"

namespace jod
{
    GLRectF RectF::ToGLRectF() const
    {
        /* Do transformation to OpenGL canvas coordinates. */
        return {x * 2 - 1.0f, 1.0f - y * 2, w * 2, h * 2};
    }
}
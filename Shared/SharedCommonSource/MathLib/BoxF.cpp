/*
 * BoxF.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */


#include "BoxF.hpp"
#include "GLBoxF.hpp"
#include "PointF.hpp"
#include "SizeF.hpp"

namespace JoD {

GLBoxF BoxF::ToGLBoxF() const {
    
    // Do transformation to OpenGL canvas coordinates.
    return {x * 2 - 1.0f, 1.0f - y * 2, w * 2, h * 2};
}

PointF BoxF::GetPosition() const {
    
    return {x, y};
}

SizeF BoxF::GetSize() const {
    
    return {w, h};
}

bool BoxF::Contains(PointF point) const {
    
    return point.x >= x && point.y >= y && point.x < x + w && point.y < y + h;
}

PointF BoxF::GetCenter() const {
    
    return {x + w/2, y + h/2};
}

}
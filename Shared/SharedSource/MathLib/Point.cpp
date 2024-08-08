/*
 * Point.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Point.hpp"

namespace JoD {

    bool Point::operator==(const Point& rhs) const {
        
        return x == rhs.x && y == rhs.y;
    }
}
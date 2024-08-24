/*
 * Point.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Point.hpp"

namespace JoD {
bool Point::operator==(const Point& rhs) const {
// Compare individual coordinate components.
    return x == rhs.x && y == rhs.y;
}

void Point::operator+=(const Point& rhs) {
// Add to individual coordinate components.
    x += rhs.x;
    y += rhs.y;
}

Point Point::Translate(int dx, int dy) const {
// Add to individual coordinate components and return.
    return {x + dx, y + dy};
}
}

/*
 * Point.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
struct Point {
/// Compare point to another.
/// @param rhs Other point to compare with.
/// @return bool True if equal, else false.
    bool operator==(const Point& rhs) const;
    
/// Add another point to this one.
/// @param rhs Other point to add.
    void operator+=(const Point& rhs);
    
/// Move point by delta values.
/// @param dx Move x coordinate by this amount.
/// @param dy Move y coordiante by this amount.
    Point Translate(int dx, int dy) const;
    
/// X coordinate.
    int x {0};
/// Y coordinate.
    int y {0};
};
}

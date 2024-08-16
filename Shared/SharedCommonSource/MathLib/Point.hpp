/*
 * Point.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    struct Point {
        
        bool operator==(const Point& rhs) const;
        
        void operator+=(const Point& rhs);
        
        Point Translate(int dx, int dy) const;
        
        // Members
        
        int x {0};
        
        int y {0};
    };
}
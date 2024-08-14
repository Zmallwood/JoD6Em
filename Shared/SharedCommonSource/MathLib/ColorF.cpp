/*
 * ColorF.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ColorF.hpp"

namespace JoD {
    
    bool ColorF::operator==(const ColorF& rhs) const {
        
        return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
    }
}
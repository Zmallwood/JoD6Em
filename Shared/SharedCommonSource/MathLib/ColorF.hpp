/*
 * ColorF.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
/// RGBA color object with color components in float type.
struct ColorF {
/// Compare color by its components.
/// @param rhs Other colorF object to compare width.
/// @return bool True if colors equal, else false.
    bool operator==(const ColorF& rhs) const;
    
/// Red component in float type in range 0.0 - 1.0.
    float r {0.0f};
/// Green component in float type in range 0.0 - 1.0.
    float g {0.0f};
/// Blue component in float type in range 0.0 - 1.0.
    float b {0.0f};
/// Alpha component in float type in range 0.0 - 1.0.
    float a {1.0f};
};
}

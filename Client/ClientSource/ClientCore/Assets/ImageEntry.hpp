/*
 * ImageEntry.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
/// An entry for storing image data in ImageBank.
struct ImageEntry {
    GLuint id {0};       ///< OpenGL ID for the stored image as a GL texture.
    Size dimensions;     ///< Dimensions for image obtained during texture initialization.
};
}

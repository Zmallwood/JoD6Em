/*
 * ImageEntry.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// An entry for storing image data in ImageBank.
    ///
    /// @details Used for every loaded image file in ImageBank.
    ///          It is needed to be able to store the image
    ///          dimensions along the the image ID.
    ///
    struct ImageEntry {
        
        GLuint id {0}; ///< OpenGL ID for the stored image as a GL texture.
        Size dimensions; ///< Dimensions for image obtained during texture initialization.
    };
}
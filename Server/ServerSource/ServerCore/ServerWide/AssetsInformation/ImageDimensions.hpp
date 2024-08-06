/*
 * ImageDimensions.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Container storing all retrieved image dimensions from users.
    ///
    class ImageDimensions {
        
      public:
        std::map<int, Size> m_dimensions; ///< Stored image dimensions with image name hash code as key.
    };
}
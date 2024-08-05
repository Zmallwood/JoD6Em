/*
 * ImageDimensions.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include <array>
#include <atomic>

namespace JoD {
    
    class ImageDimensions {
      public:
        std::map<int, Size> m_dimensions;
    };
}
/*
 * PointF.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    /// @brief Point with float coordinates.
    struct PointF {
        float x = 0.0f; ///< X coordinate in float type.
        float y = 0.0f; ///< Y coordinate in float type.
    };
}
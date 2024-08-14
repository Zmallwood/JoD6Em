/*
 * NetConfiguration.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Commonly used constants related to networking.
    ///
    namespace NetConstants {
        
        constexpr float k_floatPrecision ///< Determines number of decimals for a sent float over web sockets.
        {10000.0f};
    }
}
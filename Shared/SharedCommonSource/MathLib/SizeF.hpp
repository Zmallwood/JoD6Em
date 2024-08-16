/*
 * SizeF.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Size with float dimension.
    ///
    struct SizeF {
        
        // Members
        
        float w {0.0f}; ///< Width in float type.
        
        float h {0.0f}; ///< Height in float type.
    };
}
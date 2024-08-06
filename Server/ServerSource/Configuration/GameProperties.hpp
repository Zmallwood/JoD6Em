/*
 * GameProperties.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Holds game configuration parameters.
    ///
    class GameProperties {
        
      public:
        const int k_numGridRows {21}; ///< Number of rows in tile grid in world view.
        const Size k_worldAreaSize {100, 100};
    };
}
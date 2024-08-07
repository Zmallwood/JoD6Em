/*
 * World.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "WorldArea.hpp"

namespace JoD {
    
    class WorldArea;
    
    ///
    /// Top-level world object, of which only one (static)
    /// instance exists and is used for all connected users.
    ///
    class World {
        
      public:
        ///
        /// Construct a new World object by creating contained world area.
        ///
        World();
        
        std::unique_ptr<WorldArea> m_currentWorldArea; ///< Currently only a single world area in the world.
    };
}
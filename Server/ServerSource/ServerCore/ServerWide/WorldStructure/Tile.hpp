/*
 * Tile.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class Mob;
    class Object;
    
    ///
    /// Represents a square tile in the game world.
    ///
    class Tile {
        
      public:
        int m_ground {0}; ///< Hash code for ground type.
        std::shared_ptr<Object> m_object; ///< Hash code for object type name, nullptr means no object.
        std::shared_ptr<Mob> m_mob; ///< Mob currently occupying this tile, nullptr means no mob.
    };
}
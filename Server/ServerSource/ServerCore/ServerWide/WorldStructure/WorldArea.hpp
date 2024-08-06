/*
 * WorldArea.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class Tile;
    class Mob;
    
    ///
    /// A portion of the total world map composed of a tile grid.
    ///
    class WorldArea {
        
      public:
        ///
        /// Construct a new World Area object by initializing tile grid structure.
        ///
        WorldArea();
        
        std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles; ///< Tile grid.
        std::map<std::shared_ptr<Mob>, Point>
        m_mobPositions; ///< Helper structure which maps mobs to their positions.
    };
}
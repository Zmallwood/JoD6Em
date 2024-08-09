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
        
        ~WorldArea();
        
        Size GetSize() const;
        
        bool IsValidCoord(Point coord) const;
        
        Tile* GetTile(Point coord) const;
        
        Tile* GetTile(int xCoord, int yCoord) const;
        
        void RegisterMobPosition(std::shared_ptr<Mob> mob, Point coord);
        
        std::optional<Point> GetMobCoord(std::shared_ptr<Mob> mob) const;
        
      private:
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}
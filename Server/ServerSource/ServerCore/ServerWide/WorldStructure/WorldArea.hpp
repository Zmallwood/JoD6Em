/*
 * WorldArea.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "MobGroup.hpp"

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
        
        bool IsValidCoord(int x, int y) const;
        
        Tile* GetTile(Point coord) const;
        
        Tile* GetTile(int xCoord, int yCoord) const;
        
        void RegisterMobPosition(std::shared_ptr<Mob> mob, Point coord);
        
        void RemoveMobPosition(std::shared_ptr<Mob> mob);
        
        std::optional<Point> GetMobCoord(std::shared_ptr<Mob> mob) const;
        
        std::vector<MobGroup> m_mobGroups;
        
      private:
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}
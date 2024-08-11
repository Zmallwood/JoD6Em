/*
 * WorldArea.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "CreatureGroup.hpp"

namespace JoD {
    
    class Tile;
    class Creature;
    
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
        
        void RegisterMobPosition(std::shared_ptr<Creature> mob, Point coord);
        
        void RemoveMobPosition(std::shared_ptr<Creature> mob);
        
        std::optional<Point> GetMobCoord(std::shared_ptr<Creature> mob) const;
        
        std::vector<CreatureGroup> m_creatureGroups;
        
      private:
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}
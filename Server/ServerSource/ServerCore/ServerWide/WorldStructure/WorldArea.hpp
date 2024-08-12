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
        
        void RegisterCreaturePosition(std::shared_ptr<Creature> creature, Point coord);
        
        void RemoveCreaturePosition(std::shared_ptr<Creature> creature);
        
        std::optional<Point> GetCreatureCoord(std::shared_ptr<Creature> creature) const;
        
        const std::map<std::shared_ptr<Creature>, Point>& GetCreaturePositions() const;
        
        std::vector<CreatureGroup> m_creatureGroups;
        
      private:
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}
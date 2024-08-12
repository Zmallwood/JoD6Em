/*
 * CreatureGroup.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class Creature;
    
    ///
    /// A group of creatures which movies across the world as a group and
    /// tries to keep a fixed amount of creatures in the group.
    ///
    class CreatureGroup {
        
      public:
        Point m_coord; ///< Coordinate of this creature group.
        std::vector<std::shared_ptr<Creature>> m_creatures; ///< Creatures belonging to this group.
        Point m_destCoord = {rand() % 100, rand() % 100}; ///< Destination to where this group is heading.
        int m_numCreaturesInGroup {6}; ///< Number of creatures which this group aims to have constantly.
    };
}
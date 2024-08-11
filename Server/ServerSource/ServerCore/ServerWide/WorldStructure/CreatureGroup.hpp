/*
 * CreatureGroup.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class Creature;
    
    class CreatureGroup {
      public:
        Point m_coord;
        std::vector<std::shared_ptr<Creature>> m_creatures;
        Point m_destCoord = {rand() % 100, rand() % 100};
        int m_numMobsInGroup {6};
    };
}
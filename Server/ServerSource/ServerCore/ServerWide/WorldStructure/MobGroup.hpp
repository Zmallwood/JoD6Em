/*
 * MobGroup.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class Mob;
    
    class MobGroup {
      public:
        Point m_coordinate;
        std::vector<std::shared_ptr<Mob>> m_mobs;
        Point m_destCoord = {rand() % 100, rand() % 100};
    };
}
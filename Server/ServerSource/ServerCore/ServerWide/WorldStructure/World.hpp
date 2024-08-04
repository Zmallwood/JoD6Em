/*
 * World.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class WorldArea;

    class World {
    public:
        World();
        
        std::shared_ptr<WorldArea> m_current_world_area;
    };
}
/*
 * world.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class world_area;

    class world {
    public:
        world();
        
        std::shared_ptr<world_area> m_current_world_area;
    };
}
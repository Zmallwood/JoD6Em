/*
 * World.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "World.h"
#include "WorldArea.h"

namespace jod {
    world::world(){
        m_current_world_area = std::make_shared<world_area>();
    }
}
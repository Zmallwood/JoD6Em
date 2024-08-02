// world.cpp
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
//

#include "world.h"
#include "world_area.h"

namespace jod {
    world::world(){
        m_currentWorldArea = std::make_shared<world_area>();
    }
}
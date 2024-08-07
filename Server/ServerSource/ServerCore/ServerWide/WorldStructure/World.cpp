/*
 * World.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "World.hpp"

namespace JoD {
    
    World::World()
        : m_currentWorldArea(std::make_unique<WorldArea>()){
        
    }
}
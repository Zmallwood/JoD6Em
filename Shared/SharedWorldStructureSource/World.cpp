/*
 * World.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "World.hpp"
#include "WorldArea.hpp"

namespace JoD {
    
    struct World::Impl {
        std::unique_ptr<WorldArea> currentWorldArea; ///< Currently only a single world area in the world.
    };
    
    World::World()
        : m_pImpl(std::make_unique<Impl>()) {
        
        m_pImpl->currentWorldArea = std::make_unique<WorldArea>();
    }
    
    World::~World() {
        
    }
    
    WorldArea* World::GetCurrWorldArea() const {
            
        return m_pImpl->currentWorldArea.get();
    }
}
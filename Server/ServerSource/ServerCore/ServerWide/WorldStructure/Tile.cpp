/*
 * Tile.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Tile.hpp"
#include "Object.hpp"

namespace JoD {
    
    struct Tile::Impl {
        int ground {0}; ///< Hash code for ground type.
        std::unique_ptr<Object> object; ///< Hash code for object type name, nullptr means no object.
        std::shared_ptr<Mob> mob; ///< Mob currently occupying this tile, nullptr means no mob.
    };
    
    Tile::Tile()
    : m_pImpl(std::make_unique<Impl>()) {
        
    }
    
    Tile::~Tile() {
        
    }
    
    int Tile::GetGround() const {
        
        return m_pImpl->ground;
    }
    
    void Tile::SetGround(int value) {
        
        m_pImpl->ground = value;
    }
    
    Object* Tile::GetObject() const {
        
        return m_pImpl->object.get();
    }
    
    void Tile::SetObject(std::unique_ptr<Object> value) {
        
        m_pImpl->object = std::move(value);
    }
    
    const std::shared_ptr<Mob> Tile::GetMob() const {
        
        return m_pImpl->mob;
    }
    
    void Tile::SetMob(std::shared_ptr<Mob> value) {
        
        m_pImpl->mob = value;
    }
}
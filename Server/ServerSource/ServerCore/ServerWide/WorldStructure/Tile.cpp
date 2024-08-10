/*
 * Tile.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Tile.hpp"
#include "ObjectsPile.hpp"

namespace JoD {
    
    struct Tile::Impl {
        int ground {0}; ///< Hash code for ground type.
        std::shared_ptr<Mob> mob; ///< Mob currently occupying this tile, nullptr means no mob.
        int elevation {0};
        int groundCover {0};
        ObjectsPile objectsPile;
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
    
    void Tile::SetGround(std::string_view imageName) {
        
        SetGround(Hash(imageName));
    }
    
    const std::shared_ptr<Mob> Tile::GetMob() const {
        
        return m_pImpl->mob;
    }
    
    void Tile::SetMob(std::shared_ptr<Mob> value) {
        
        m_pImpl->mob = value;
    }
    
    int Tile::GetElevation() const {
        
        return m_pImpl->elevation;
    }
    
    void Tile::SetElevation(int value) {
        
        m_pImpl->elevation = value;
    }
    
    int Tile::GetGroundCover() const {
        
        
        return m_pImpl->groundCover;
    }
    
    void Tile::SetGroundCover(int value) {
        
        m_pImpl->groundCover = value;
    }
    
    
    ObjectsPile &Tile::GetObjectsPile() const {
        
        return m_pImpl->objectsPile;
    }
}
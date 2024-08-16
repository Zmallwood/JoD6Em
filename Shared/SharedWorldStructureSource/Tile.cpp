/*
 * Tile.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Tile.hpp"
#include "ObjectsPile.hpp"
#include "NPC.hpp"

namespace JoD {
    
    struct Tile::Impl {
        int ground {0};                     ///< Hash code for ground type.
        std::shared_ptr<Creature> creature; ///< Creature currently occupying this tile, nullptr means no creature.
        int elevation {0};
        int groundCover {0};
        ObjectsPile objectsPile;
        std::shared_ptr<NPC> npc;
    };
    
    Tile::Tile()
        : m_pImpl(std::make_unique<Impl>()) {}
    
    Tile::~Tile() {}
    
    int Tile::GetGround() const {
        
        return m_pImpl->ground;
    }
    
    void Tile::SetGround(int value) {
        
        m_pImpl->ground = value;
    }
    
    void Tile::SetGround(std::string_view imageName) {
        
        SetGround(Hash(imageName));
    }
    
    const std::shared_ptr<Creature> Tile::GetCreature() const {
        
        return m_pImpl->creature;
    }
    
    void Tile::SetCreature(std::shared_ptr<Creature> value) {
        
        m_pImpl->creature = value;
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
    
    
    
    std::shared_ptr<NPC> Tile::GetNPC() const {
        
        return m_pImpl->npc;
    }
    
    void Tile::SetNPC(std::shared_ptr<NPC> npc) {
        
        m_pImpl->npc = npc;
    }
}
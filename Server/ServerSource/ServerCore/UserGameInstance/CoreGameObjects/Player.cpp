/*
 * Player.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Player.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"

namespace JoD {
    
    void Player::TryMoveNorth() {
        
        TryMoveToCoord({m_coord.x, m_coord.y - 1});
    }
    
    void Player::TryMoveEast() {
        
        TryMoveToCoord({m_coord.x + 1, m_coord.y});
    }
    
    void Player::TryMoveSouth() {
        
        TryMoveToCoord({m_coord.x, m_coord.y + 1});
    }
    
    void Player::TryMoveWest() {
        
        TryMoveToCoord({m_coord.x - 1, m_coord.y});
    }
    
    void Player::TryMoveNorthEast() {
        
        TryMoveToCoord({m_coord.x + 1, m_coord.y - 1});
    }
    
    void Player::TryMoveSouthEast() {
        
        TryMoveToCoord({m_coord.x + 1, m_coord.y + 1});
    }
    
    void Player::TryMoveSouthWest() {
        
        TryMoveToCoord({m_coord.x - 1, m_coord.y + 1});
    }
    
    void Player::TryMoveNorthWest() {
        
        TryMoveToCoord({m_coord.x - 1, m_coord.y - 1});
    }
    
    void Player::TryMoveToCoord(Point coord) {
        
        const auto &worldArea = _<World>().GetCurrentWorldArea();
        
        if (!worldArea->IsValidCoord(coord)) {
            
            return;
        }
        
        const auto tile = worldArea->GetTile(coord);
        
        if (tile->GetGround() == Hash("GroundWater")) {
            
            return;
        }
        
        if (tile->GetObject()) {
            
            return;
        }
        
        if (tile->GetMob()) {
            
            return;
        }
        
        m_coord = coord;
    }
}
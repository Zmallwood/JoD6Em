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
    
    void Player::TryMoveNorth(UserID userID) {
        
        TryMoveToCoord(userID, {m_coord.x, m_coord.y - 1});
    }
    
    void Player::TryMoveEast(UserID userID) {
        
        TryMoveToCoord(userID, {m_coord.x + 1, m_coord.y});
    }
    
    void Player::TryMoveSouth(UserID userID) {
        
        TryMoveToCoord(userID, {m_coord.x, m_coord.y + 1});
    }
    
    void Player::TryMoveWest(UserID userID) {
        
        TryMoveToCoord(userID, {m_coord.x - 1, m_coord.y});
    }
    
    void Player::TryMoveNorthEast(UserID userID) {
        
        TryMoveToCoord(userID, {m_coord.x + 1, m_coord.y - 1});
    }
    
    void Player::TryMoveSouthEast(UserID userID) {
        
        TryMoveToCoord(userID, {m_coord.x + 1, m_coord.y + 1});
    }
    
    void Player::TryMoveSouthWest(UserID userID) {
        
        TryMoveToCoord(userID, {m_coord.x - 1, m_coord.y + 1});
    }
    
    void Player::TryMoveNorthWest(UserID userID) {
        
        TryMoveToCoord(userID, {m_coord.x - 1, m_coord.y - 1});
    }
    
    void Player::TryMoveToCoord(UserID userID, Point coord) {
        
        const auto &worldArea = _<World>().GetCurrentWorldArea();
        
        if (!worldArea->IsValidCoord(coord)) {
            
            return;
        }
        
        const auto &tile = worldArea->GetTile(coord);
        
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
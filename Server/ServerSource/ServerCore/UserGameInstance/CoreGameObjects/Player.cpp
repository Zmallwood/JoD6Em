/*
 * Player.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Player.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Object.hpp"
#include "ObjectsPile.hpp"
#include "Configuration/ObjectsIndex.hpp"

namespace JoD {

void Player::TryMove(UserID userID, Directions direction) {
    
    switch (direction) {
    
    case Directions::North:
// Decrease y by 1.
        TryMoveToCoord(userID, m_coord.Translate(0, -1));
        break;
        
    case Directions::NorthEast:
// Increase x by 1 and decrease y by 1.
        TryMoveToCoord(userID, m_coord.Translate(1, -1));
        break;
        
    case Directions::East:
// Increase x by 1.
        TryMoveToCoord(userID, m_coord.Translate(1, 0));
        break;
        
    case Directions::SouthEast:
// Increase x and y by one.
        TryMoveToCoord(userID, m_coord.Translate(1, 1));
        break;
        
    case Directions::South:
// Increase y by 1.
        TryMoveToCoord(userID, m_coord.Translate(0, 1));
        break;
        
    case Directions::SouthWest:
// Decrease x by 1 and increase y by 1.
        TryMoveToCoord(userID, m_coord.Translate(-1, 1));
        break;
        
    case Directions::West:
// Decrease x by 1.
        TryMoveToCoord(userID, m_coord.Translate(-1, 0));
        break;
        
    case Directions::NorthWest:
// Decrease x and y by 1.
        TryMoveToCoord(userID, m_coord.Translate(-1, -1));
        break;
        
    case Directions::None:
        break;
    }
}

void Player::Hit(int damage) {
    
// Reduce damage amount from health points.
    m_hp -= damage;
}

void Player::ResetExp() {
    
    m_exp = 0;
}

void Player::AddExp(int value) {
    
    m_exp += value;
}

void Player::TryMoveToCoord(UserID userID, Point coord) {
    
    const auto &worldArea = _<World>().GetCurrWorldArea();
    
// Cannot move outside world area.
    if (!worldArea->IsValidCoord(coord)) {
        
        return;
    }
    
    const auto &tile = worldArea->GetTile(coord);
    
// Cannot move to water tile.
    if (tile->GetGround() == Hash("GroundWater")) {
        
        return;
    }
    
// Cannot move to a tile blocked by a creature.
    if (tile->GetCreature()) {
        
        return;
    }
    
// Do check if destination tile has an object which is considered an obstace.
    
    auto canWalkThroughObject = true;
    
// Loop through all objects on destination tile.
    for (auto object : tile->GetObjectsPile().GetObjects()) {
        
// Check in ObjectsIndex if object exists and allows walking through it or not.
        if (!_<ObjectsIndex>().CanWalkThroughObject(object->GetType())) {
            
            canWalkThroughObject = false;
            
// If cannot walk through a single object its enough for blocket the player
// and we dont need to continue the check.
            break;
        }
    }
    
// Destination tile was blocked, cancel movement attempt.
    if (!canWalkThroughObject) {
        
        return;
    }
    
// Destination tile passed all tests, move the player to its coordinate.
    m_coord = coord;
}

}
/*
 * UpdateAnimalsEating.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "UpdateAnimalsEating.hpp"
#include "Tile.hpp"
#include "ObjectsPile.hpp"
#include "Object.hpp"

namespace JoD {
    
    void UpdateAnimalsEating(Tile* tile) {
        
        auto objects = tile->GetObjectsPile().GetObjects();
        
        for (auto object : objects) {
            
            // Find grass object on ground.
            if (object->GetType() == Hash("ObjectGrass")) {
                
                // Reduce its durability, as the creature is eating from it.
                object->SetDurability(object->GetDurability() - 1.0f);
                
                // Remove it if durability reaches zero.
                if (object->GetDurability() <= 0.0f) {
                    
                    tile->GetObjectsPile().RemoveObject(object);
                }
            }
        }
    }
}
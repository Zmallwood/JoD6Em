/*
 * UpdateObjects.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "UpdateObjects.hpp"
#include "Tile.hpp"
#include "ObjectsPile.hpp"
#include "Object.hpp"

namespace JoD {

namespace {

static constexpr Duration k_remainsStayDuration {Millis(5000)};

}

void UpdateObjects(Tile* tile) {
    
// Get all objects on tile.
    
    auto objects = tile->GetObjectsPile().GetObjects();
    
    for (auto object : objects) {
        
// If object is of type ObjectBoneRemains...
        
        if (object->GetType() == Hash("ObjectBoneRemains")) {
            
// If object has existed long enough...
            
            if (Now() > object->GetCreationTime() + k_remainsStayDuration) {
                
// Remove it.
                
                tile->GetObjectsPile().RemoveObject(object);
            }
        }
    }
}

}
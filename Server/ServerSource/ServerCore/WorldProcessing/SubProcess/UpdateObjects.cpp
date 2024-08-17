/*
 * UpdateObjects.cpp
 *
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
    
    auto objects = tile->GetObjectsPile().GetObjects();
    
    for (auto object : objects) {
        
        if (object->GetType() ==
            Hash("ObjectBoneRemains")) {
            
            if (Now() >
                object->GetCreationTime() +
                k_remainsStayDuration) {
                
                tile->GetObjectsPile().RemoveObject(
                    object);
            }
        }
    }
}

}
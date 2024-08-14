/*
 * ObjectsIndex.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ObjectsIndex.hpp"
#include "ObjectFlags.hpp"

namespace JoD {
    
    ObjectsIndex::ObjectsIndex() {
        
        // Insert object flags for certain objects.
        m_objectFlags.insert(
            {Hash("ObjectPinkFlower"),
             ObjectFlags::k_walkThrough});
        m_objectFlags.insert({Hash("ObjectGrass"), ObjectFlags::k_walkThrough});
    }
    
    bool ObjectsIndex::CanWalkThroughObject(int objectNameHash) const {
        
        // Check if object type exists in storage.
        if (m_objectFlags.contains(objectNameHash)) {
            
            // If it does, return wether it has the walk-through flag or not.
            return (m_objectFlags.at(objectNameHash) &
                    ObjectFlags::k_walkThrough) != 0;
        }
        
        // Return false as default, if the object type doesnt exist in storage.
        return false;
    }
}
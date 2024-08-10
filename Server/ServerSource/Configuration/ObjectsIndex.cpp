/*
 * ObjectsIndex.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ObjectsIndex.hpp"
#include "ObjectFlags.hpp"

namespace JoD {

    ObjectsIndex::ObjectsIndex() {
        
        m_objectFlags.insert({Hash("ObjectPinkFlower"), ObjectFlags::k_walkThrough});
    }
    
    bool ObjectsIndex::CanWalkThroughObject(int objectNameHash) const {
        
        if (m_objectFlags.contains(objectNameHash)) {
            
            return (m_objectFlags.at(objectNameHash) & ObjectFlags::k_walkThrough) != 0;
        }
        
        return false;
    }
}
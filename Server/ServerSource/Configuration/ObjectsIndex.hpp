/*
 * ObjectsIndex.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class ObjectsIndex {
      public:
        ObjectsIndex();
        
        bool CanWalkThroughObject(int objectNameHash) const;
        
        std::map<int, int> m_objectFlags;
    };
}
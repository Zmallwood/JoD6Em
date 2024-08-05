/*
 * GenerateObjects.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateObjects.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"

namespace JoD {
    
    void GenerateObjects(std::shared_ptr<WorldArea> worldArea) {
        
        auto numObjectsTree1s = 300;
        
        for (auto i = 0; i < numObjectsTree1s; i++) {
            
            auto x = rand() % 100;
            auto y = rand() % 100;
            
            if (worldArea->m_tiles[x][y]->m_ground !=
                Hash("GroundWater")) {
                
                worldArea->m_tiles[x][y]->m_object = Hash("ObjectTree1");
            }
        }
    }
}
/*
 * GenerateObjects.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateObjects.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"

namespace JoD {
    
    namespace {
        
        void GenerateObjectOfType(
            std::shared_ptr<WorldArea> worldArea, std::string_view objectName,
            int amount);
    }
    
    void GenerateObjects(std::shared_ptr<WorldArea> worldArea) {
        
        GenerateObjectOfType(worldArea, "ObjectTree1", 300);
        GenerateObjectOfType(worldArea, "ObjectTree2", 300);
    }
    
    namespace {
        
        void GenerateObjectOfType(
            std::shared_ptr<WorldArea> worldArea, std::string_view objectName,
            int amount) {
            
            for (auto i = 0; i < amount; i++) {
                
                auto x = rand() % 100;
                auto y = rand() % 100;
                
                if (worldArea->m_tiles[x][y]->m_ground !=
                    Hash("GroundWater")) {
                    
                    worldArea->m_tiles[x][y]->m_object = Hash(objectName);
                }
            }
        }
    }
}
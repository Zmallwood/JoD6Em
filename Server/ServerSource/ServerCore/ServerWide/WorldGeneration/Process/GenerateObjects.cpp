/*
 * GenerateObjects.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateObjects.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/Object.hpp"
#include "Configuration/GameProperties.hpp"

namespace JoD {
    
    namespace {
        
        void GenerateObjectOfType(
            std::shared_ptr<WorldArea> worldArea, std::string_view objectName,
            int amount);
    }
    
    void GenerateObjects(std::shared_ptr<WorldArea> worldArea) {
        
        GenerateObjectOfType(worldArea, "ObjectTree1", 300);
        GenerateObjectOfType(worldArea, "ObjectTree2", 300);
        GenerateObjectOfType(worldArea, "ObjectBush1", 200);
        GenerateObjectOfType(worldArea, "ObjectPinkFlower", 200);
    }
    
    namespace {
        
        void GenerateObjectOfType(
            std::shared_ptr<WorldArea> worldArea, std::string_view objectName,
            int amount) {
            
            for (auto i = 0; i < amount; i++) {
                
                const auto x = rand() % _<GameProperties>().k_worldAreaSize.w;
                const auto y = rand() % _<GameProperties>().k_worldAreaSize.h;
                
                const auto ground = worldArea->m_tiles[x][y]->m_ground;
                
                if (ground != Hash("GroundWater") && ground != Hash("GroundCobbleStone")) {
                    
                    worldArea->m_tiles[x][y]->m_object = std::make_shared<Object>(objectName);
                }
            }
        }
    }
}
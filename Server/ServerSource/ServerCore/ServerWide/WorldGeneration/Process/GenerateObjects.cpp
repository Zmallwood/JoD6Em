/*
 * GenerateObjects.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateObjects.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/ObjectsPile.hpp"
#include "Configuration/GameProperties.hpp"

namespace JoD {
    
    namespace {
        
        void GenerateObjectOfType(
            WorldArea* worldArea, std::string_view objectName,
            int amount);
    }
    
    void GenerateObjects(WorldArea* worldArea) {
        
        for (auto y = 0; y < _<GameProperties>().GetWorldAreaSize().h; y++) {
            
            for (auto x = 0; x < _<GameProperties>().GetWorldAreaSize().w;
                 x++) {
                
                if (worldArea->GetTile(x,y)->GetGround() == Hash("GroundGrass")) {
                    
                    worldArea->GetTile(
                        x,
                        y)->GetObjectsPile().AddObject("ObjectGrass");
                }
            }
        }
        
        GenerateObjectOfType(worldArea, "ObjectTree1", 300);
        GenerateObjectOfType(worldArea, "ObjectTree2", 300);
        GenerateObjectOfType(worldArea, "ObjectBush1", 200);
        GenerateObjectOfType(worldArea, "ObjectPinkFlower", 200);
    }
    
    namespace {
        
        void GenerateObjectOfType(
            WorldArea* worldArea, std::string_view objectName,
            int amount) {
            
            for (auto i = 0; i < amount; i++) {
                
                const auto x = rand() %
                               _<GameProperties>().GetWorldAreaSize().w;
                const auto y = rand() %
                               _<GameProperties>().GetWorldAreaSize().h;
                
                const auto ground = worldArea->GetTile(x, y)->GetGround();
                
                if (ground != Hash("GroundWater") &&
                    ground != Hash("GroundCobbleStone") &&
                    ground != Hash("GroundBridge")) {
                    
                    worldArea->GetTile(
                        x,
                        y)->GetObjectsPile().AddObject(objectName);
                }
            }
        }
    }
}
/*
 * GenerateObjects.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateObjects.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "ObjectsPile.hpp"
#include "Configuration/GameProperties.hpp"

namespace JoD {
    
    namespace {
        
        // Packed arguments for GenerateObjectOfType() function.
        struct GenerateObjectOfTypeArgs {
            
            WorldArea* worldArea;
            std::string objectName;
            int amount;
        };
        
        // Generate a certain amount of objects of specific type.
        void GenerateObjectOfType(GenerateObjectOfTypeArgs args);
        
        void GenerateGrassOverWholeWorldArea(WorldArea* worldArea);
    }
    
    void GenerateObjects(WorldArea* worldArea) {
        
        // Add grass.
        GenerateGrassOverWholeWorldArea(worldArea);
        
        // Generate certain amount of objects of different types.
        
        GenerateObjectOfType(
            {.worldArea = worldArea,
             .objectName = "ObjectTree1", .amount = 300});
        
        GenerateObjectOfType(
            {.worldArea = worldArea,
             .objectName = "ObjectTree2", .amount = 200});
        
        GenerateObjectOfType(
            {.worldArea = worldArea,
             .objectName = "ObjectPinkFlower", .amount = 200});
    }
    
    namespace {
        
        void GenerateObjectOfType(GenerateObjectOfTypeArgs args) {
            
            for (auto i = 0; i < args.amount; i++) {
                
                // Randomize coordinate for new object.
                
                const auto x =
                    rand() %
                    _<GameProperties>().GetWorldAreaSize().w;
                
                const auto y =
                    rand() %
                    _<GameProperties>().GetWorldAreaSize().h;
                
                const auto ground = args.worldArea->GetTile(x, y)->GetGround();
                
                // Dont add objects on water or roads.
                if (ground != Hash("GroundWater") &&
                    ground != Hash("GroundCobbleStone") &&
                    ground != Hash("GroundBridge")) {
                    
                    // Add the object to the tile.
                    args.worldArea->GetTile(
                        x,
                        y)->GetObjectsPile().AddObject(args.objectName);
                }
            }
        }
        
        void GenerateGrassOverWholeWorldArea(WorldArea* worldArea) {
            
            // Loop over whole world area.
            
            for (auto y = 0; y < _<GameProperties>().GetWorldAreaSize().h; y++){
                
                for (auto x = 0; x < _<GameProperties>().GetWorldAreaSize().w;
                     x++) {
                    
                    // Only add grass object on ground of grass type.
                    if (worldArea->GetTile(
                            x,
                            y)->GetGround() ==
                        Hash("GroundGrass")) {
                        
                        worldArea->GetTile(
                            x,
                            y)->GetObjectsPile().AddObject("ObjectGrass");
                    }
                }
            }
        }
    }
}
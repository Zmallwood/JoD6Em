/*
 * GenerateRoads.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateRoads.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"

namespace JoD {
    
    namespace {
        
        // Argument packing for GenerateRoadSection() function.
        struct RoadGenerateArgs {
            
            WorldArea* worldArea;
            Point startCoord;
            Point deltaStep;
            int numSteps;
        };
        
        // Generate roads for a distance of tiles in the world area.
        Point GenerateRoadSection(RoadGenerateArgs args);
    }
    
    void GenerateRoads(WorldArea* worldArea) {
        
        // Start generating roads from top left corner of the world area.
        auto coord = Point {0, 0};
        
        // Generate diagonal roads in south east direction.
        coord = GenerateRoadSection(
            {.worldArea = worldArea,
             .startCoord = coord, .deltaStep = {1, 1},
             .numSteps = 25});
        
        // Generate straight road to the east.
        coord = GenerateRoadSection(
            {.worldArea = worldArea,
             .startCoord = coord, .deltaStep = {1, 0},
             .numSteps = 50});
        
        // Generate straight road to the south.
        coord = GenerateRoadSection(
            {.worldArea = worldArea,
             .startCoord = coord, .deltaStep = {0, 1},
             .numSteps = 50});
        
        // Generate straight road to the west.
        coord = GenerateRoadSection(
            {.worldArea = worldArea,
             .startCoord = coord, .deltaStep = {-1, 0},
             .numSteps = 50});
        
        // Generate straight road to the south.
        coord = GenerateRoadSection(
            {.worldArea = worldArea,
             .startCoord = coord, .deltaStep = {0, 1},
             .numSteps = 25});
    }
    
    namespace {
        
        Point GenerateRoadSection(RoadGenerateArgs args) {
            
            auto coord = args.startCoord;
            
            // Iterate the provided distance of steps.
            for (auto i = 0; i < args.numSteps; i++) {
                
                auto tile = args.worldArea->GetTile(coord);
                
                // If ground is not water...
                if (tile->GetGround() != Hash("GroundWater")) {
                    
                    // Then create cobblestone.
                    tile->SetGround("GroundCobbleStone");
                }
                // Else if ground is water...
                else {
                    
                    // Then create bridge.
                    tile->SetGround("GroundBridge");
                }
                
                // Move to next tile.
                coord += args.deltaStep;
            }
            
            // Return the final tile which the generation ended on.
            return coord;
        }
    }
}
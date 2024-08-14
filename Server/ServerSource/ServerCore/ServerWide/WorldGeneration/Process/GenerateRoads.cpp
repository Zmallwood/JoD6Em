/*
 * GenerateRoads.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateRoads.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"

namespace JoD {
    
    void GenerateRoads(WorldArea* worldArea) {
        
        auto roadX = 0;
        auto roadY = 0;
        
        for (auto i = 0; i < 25; i++) {
            
            auto tile = worldArea->GetTile(roadX, roadY);
            
            if (tile->GetGround() != Hash("GroundWater")) {
                
                tile->SetGround("GroundCobbleStone");
            }
            else {
                
                tile->SetGround("GroundBridge");
            }
                
            roadX++;
            roadY++;
        }
        
        for (auto i = 0; i < 50; i++) {
            
            auto tile = worldArea->GetTile(roadX, roadY);
            
            if (tile->GetGround() != Hash("GroundWater")) {
                
                tile->SetGround("GroundCobbleStone");
            }
            else {
                
                tile->SetGround("GroundBridge");
            }
                
            roadX++;
        }
        
        for (auto i = 0; i < 50; i++) {
            
            auto tile = worldArea->GetTile(roadX, roadY);
            
            if (tile->GetGround() != Hash("GroundWater")) {
                
                tile->SetGround("GroundCobbleStone");
            }
            else {
                
                tile->SetGround("GroundBridge");
            }
                
            roadY++;
        }
        
        for (auto i = 0; i < 50; i++) {
            
            auto tile = worldArea->GetTile(roadX, roadY);
            
            if (tile->GetGround() != Hash("GroundWater")) {
                
                tile->SetGround("GroundCobbleStone");
            }
            else {
                
                tile->SetGround("GroundBridge");
            }
                
            roadX--;
        }
        
        for (auto i = 0; i < 25; i++) {
            
            auto tile = worldArea->GetTile(roadX, roadY);
            
            if (tile->GetGround() != Hash("GroundWater")) {
                
                tile->SetGround("GroundCobbleStone");
            }
            else {
                
                tile->SetGround("GroundBridge");
            }
                
            roadY++;
        }
    }
}
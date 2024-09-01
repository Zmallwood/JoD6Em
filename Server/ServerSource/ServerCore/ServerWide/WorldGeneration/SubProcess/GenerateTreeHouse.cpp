/*
 * GenerateTreeHouse.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateTreeHouse.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "ObjectsPile.hpp"

namespace JoD {
void GenerateTreeHouse(WorldArea* worldArea) {
    
    auto coord = Point{28, 28};
    
    
    for (auto y = coord.y - 3; y <= coord.y + 3; y++) {
        for (auto x = coord.x - 3; x <= coord.x + 3; x++) {
            worldArea->GetTile(x,y)->SetGround("GroundGrass");   
        }
    }
    
    auto tile = worldArea->GetTile(coord);
    
    tile->SetGround("GroundGrass");
    
    tile->GetObjectsPile().AddObject("ObjectTreeTrunkStart");
    
    tile->SetAbove(std::make_unique<Tile>());
    
    auto above = tile->GetAbove();
    above->GetObjectsPile().AddObject("ObjectTreeTrunkMid");
    
    above->SetAbove(std::make_unique<Tile>());
    
    above = above->GetAbove();
    above->GetObjectsPile().AddObject("ObjectTreeTop");
    
    // Add floor
    
    for (auto y = coord.y - 1; y <= coord.y + 1; y++) {
        for (auto x = coord.x - 1; x <= coord.x + 1; x++) {
            if (x == coord.x && y == coord.y )
                continue;

            auto tileGround = worldArea->GetTile(x, y);
            
            tileGround->SetAbove(std::make_unique<Tile>());
            
            auto tileAbove = tileGround->GetAbove();
            tileAbove->SetGround("GroundWoodFloor");      
            
            if (x == coord.x - 1) {
                if (y == coord.y)
                    tileAbove->GetObjectsPile().AddObject("ObjectWoodWallWindowedE");
                else
                    tileAbove->GetObjectsPile().AddObject("ObjectWoodWallE");
            }        
            
            if (y == coord.y - 1) {
                if (x == coord.x)
                    tileAbove->GetObjectsPile().AddObject("ObjectWoodWallWindowedS");
                else
                    tileAbove->GetObjectsPile().AddObject("ObjectWoodWallS");
            }      
        }
    }
    
    worldArea->GetTile(coord.x - 1, coord.y + 1)->GetAbove()->SetGround("GroundWoodFloorOpening");
    worldArea->GetTile(coord.x - 1, coord.y + 1)->SetElevation(0);
    worldArea->GetTile(coord.x - 1, coord.y + 1)->GetObjectsPile().Clear();
    worldArea->GetTile(coord.x - 1, coord.y + 1)->GetObjectsPile().AddObject("ObjectLadder");
}
}
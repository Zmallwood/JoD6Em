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
    
    auto tile = worldArea->GetTile(coord);
    
    tile->SetGround("GroundGrass");
    
    tile->GetObjectsPile().AddObject("ObjectTreeTrunkStart");
    
    tile->SetAbove(std::make_unique<Tile>());
    
    auto above = tile->GetAbove();
    above->GetObjectsPile().AddObject("ObjectTreeTrunkMid");
    
    above->SetAbove(std::make_unique<Tile>());
    
    above = above->GetAbove();
    above->GetObjectsPile().AddObject("ObjectTreeTop");
}
}
/*
 * GenerateRoads.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateRoads.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"

namespace JoD {
    
    void GenerateRoads(const std::unique_ptr<WorldArea> &worldArea) {
        
        auto roadX = 0;
        auto roadY = 0;
        
        for (auto i = 0; i < 25; i++) {
            
            worldArea->m_tiles[roadX][roadY]->SetGround(
                Hash("GroundCobbleStone"));
                
            roadX++;
            roadY++;
        }
        
        for (auto i = 0; i < 50; i++) {
            
            worldArea->m_tiles[roadX][roadY]->SetGround(
                Hash("GroundCobbleStone"));
                
            roadX++;
        }
        
        for (auto i = 0; i < 50; i++) {
            
            worldArea->m_tiles[roadX][roadY]->SetGround(
                Hash("GroundCobbleStone"));
                
            roadY++;
        }
        
        for (auto i = 0; i < 50; i++) {
            
            worldArea->m_tiles[roadX][roadY]->SetGround(
                Hash("GroundCobbleStone"));
                
            roadX--;
        }
        
        for (auto i = 0; i < 25; i++) {
            
            worldArea->m_tiles[roadX][roadY]->SetGround(Hash("GroundCobbleStone"));
                
            roadY++;
        }
    }
}
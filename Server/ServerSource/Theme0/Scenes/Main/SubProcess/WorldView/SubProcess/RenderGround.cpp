/*
 * RenderGround.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderGround.hpp"
#include "Tile.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {

void RenderGround(
    UserID userID,
    Tile* tile, BoxF tileBounds, Tile* tileW, Tile* tileN, int playerElev) {
    
    auto elevation = tile->GetElevation();
    
    for (auto i = 0; i < elevation; i++) {
        
        auto boundsElevS = BoxF {tileBounds.x - tileBounds.w*0.25f,
                                 tileBounds.y, tileBounds.w*1.25f,
                                 tileBounds.h};
        auto boundsElevE = BoxF {tileBounds.x,
                                 tileBounds.y - tileBounds.h*0.25f,
                                 tileBounds.w, tileBounds.h*1.25f};
        
        SendImageDrawInstruction(
            userID,
            "ElevationS",
            boundsElevS);
        
        SendImageDrawInstruction(
            userID,
            "ElevationE",
            boundsElevE);
        
        tileBounds.x -= tileBounds.w/8;
        tileBounds.y -= tileBounds.h/4;
    }
    
    auto ground = tile->GetGround();
    
    if (ground == Hash("GroundWater")) {
        
        const auto animIndex =
            ((std::chrono::high_resolution_clock::now().
              time_since_epoch().count()/1000000)%1200)/400;
        
        ground = Hash("GroundWater_" + std::to_string(animIndex));
    }
    
    SendImageDrawInstruction(
        userID,
        ground,
        tileBounds);
    
    auto groundCover = tile->GetGroundCover();
    
    if (groundCover) {
        
        SendImageDrawInstruction(
            userID,
            groundCover,
            tileBounds);
    }
    
    if (tileW) {
        
        if (tileW->GetElevation() < tile->GetElevation()) {
            
            
            SendImageDrawInstruction(
                userID,
                "ElevationW",
                tileBounds);
        }
    }
    
    if (tileN) {
        
        if (tileN->GetElevation() < tile->GetElevation()) {
            
            
            SendImageDrawInstruction(
                userID,
                "ElevationN",
                tileBounds);
        }
    }
}

}
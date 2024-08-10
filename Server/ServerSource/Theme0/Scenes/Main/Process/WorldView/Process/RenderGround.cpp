/*
 * RenderGround.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderGround.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    
    void RenderGround(
        WebSocket &webSocket,
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
                webSocket,
                "ElevationS",
                boundsElevS);
            
            SendImageDrawInstruction(
                webSocket,
                "ElevationE",
                boundsElevE);
            
            tileBounds.x -= tileBounds.w/4;
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
            webSocket,
            ground,
            tileBounds);
        
        auto groundCover = tile->GetGroundCover();
        
        if (groundCover) {
            
            SendImageDrawInstruction(
                webSocket,
                groundCover,
                tileBounds);
        }
        
        if (tileW) {
            
            if (tileW->GetElevation() < tile->GetElevation()) {
                
                
                SendImageDrawInstruction(
                    webSocket,
                    "ElevationW",
                    tileBounds);
            }
        }
        
        if (tileN) {
            
            if (tileN->GetElevation() < tile->GetElevation()) {
                
                
                SendImageDrawInstruction(
                    webSocket,
                    "ElevationN",
                    tileBounds);
            }
        }
    }
}
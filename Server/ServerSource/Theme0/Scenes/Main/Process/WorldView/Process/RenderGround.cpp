/*
 * RenderGround.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderGround.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    
    void RenderGround(
        WebSocket &webSocket,
        Tile* tile, BoxF tileBounds) {
        
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
    }
}
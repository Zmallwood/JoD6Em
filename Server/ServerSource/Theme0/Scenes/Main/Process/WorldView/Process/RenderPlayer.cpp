/*
 * RenderPlayer.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderPlayer.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/UserGameInstance/EngineInstance.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
    
    void RenderPlayer(
        UserID userID, WebSocket &webSocket,
        Point coordinate, BoxF tileBounds) {
        
        const auto playerCoordinate =
            _<EngineGet>().GetPlayer(userID)->Coord();
        
        if (coordinate == playerCoordinate){
            
            SendImageDrawInstruction(
                webSocket, "Player", tileBounds);
        }
    }
}
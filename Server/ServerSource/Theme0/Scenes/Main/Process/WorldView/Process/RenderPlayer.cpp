/*
 * RenderPlayer.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderPlayer.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    
    void RenderPlayer(
        const UserGameInstanceEngine& userGameInstanceEngine, WebSocket &webSocket,
        Point coordinate, BoxF tileBounds) {
        
        const auto playerCoordinate =
            userGameInstanceEngine.m_player->m_coord;
        
        if (coordinate.x == playerCoordinate.x &&
            coordinate.y == playerCoordinate.y){
            
            SendImageDrawInstruction(
                webSocket, "Player", tileBounds);
        }
    }
}
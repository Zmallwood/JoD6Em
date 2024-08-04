/*
 * RenderPlayer.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderPlayer.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"

namespace JoD {
    void RenderPlayer(
        UserConnection& userConnection, WebSocket &webSocket,
        Point coordinate, RectF tileBounds) {
        auto playerCoordinate =
            userConnection.m_player->m_coordinate;
        if (coordinate.x == playerCoordinate.x &&
            coordinate.y == playerCoordinate.y){
            userConnection.SendImageDrawInstruction(
                webSocket, "Player", tileBounds);
        }
    }
}
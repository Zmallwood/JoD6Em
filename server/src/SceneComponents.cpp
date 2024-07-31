// Copyright (c) 2024 Andreas Åkerberg.
#include "SceneComponents.h"
#include "Client.h"
#include "Math.h"
#include "Player.h"
#include "Configuration.h"
#include "ClientCore.h"

namespace jod {
    TileHovering::TileHovering(Client &client) : m_client(client){
    }
    void TileHovering::Update(){
        auto tileSize = CalcTileSize(m_client.GetAspectRatio());
        auto playerCoord = m_client.m_player->m_coord;
        auto numRows = _<GameProperties>().numGridRows;
        auto numCols = numRows;
        auto tileX = playerCoord.x - (numCols - 1) / 2 +
                     static_cast<int>(m_client.m_mousePosition.x / tileSize.w);
        auto tileY = playerCoord.y - (numRows - 1) / 2 +
                     static_cast<int>(m_client.m_mousePosition.y / tileSize.h);
        m_hoveredCoordinate = {tileX, tileY};
    }
    MouseMovement::MouseMovement(Client &client) : m_client(client){
    }
    void MouseMovement::Update(){
        auto mouseDown = m_client.m_serverEngine->m_mouseInput->m_leftButton->IsPressedPickResult();
        auto player = m_client.m_player;
        auto hoveredTile = m_client.m_tileHovering->m_hoveredCoordinate;
        if (mouseDown)
            player->m_destination = hoveredTile;
        if (player->m_destination.x != -1 && player->m_destination.y != -1){
            auto dx = player->m_destination.x - player->m_coord.x;
            auto dy = player->m_destination.y - player->m_coord.y;
            auto absdx = std::abs(dx);
            auto absdy = std::abs(dy);
            auto normx = 0;
            auto normy = 0;
            if (dx) normx = dx / absdx;
            if (dy) normy = dy / absdy;
            player->m_coord.x += normx;
            player->m_coord.y += normy;
        }
    }
}
// Copyright (c) 2024 Andreas Åkerberg.
#include "scene_components.h"
#include "client.h"
#include "math.h"
#include "player.h"
#include "configuration.h"
#include "client_core.h"
namespace jod {
    tile_hovering::tile_hovering(client &client) : m_client(client){
    }
    void
    tile_hovering::update(){
        auto tileSize = calc_tile_size(m_client.get_aspect_ratio());
        auto playerCoord = m_client.m_player->m_coord;
        auto numRows = _<game_properties>().numGridRows;
        auto numCols = numRows;
        auto tileX =
            playerCoord.x - (numCols - 1) / 2 +
            static_cast<int>(m_client.m_mousePosition.x / tileSize.w);
        auto tileY =
            playerCoord.y - (numRows - 1) / 2 +
            static_cast<int>(m_client.m_mousePosition.y / tileSize.h);
        m_hoveredCoordinate = {tileX, tileY};
    }
    mouse_movement::mouse_movement(client &client) : m_client(client){
    }
    void
    mouse_movement::update(){
        auto mouseDown = m_client.m_serverEngine->m_mouseInput->m_leftButton->is_pressed_pick_result();
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
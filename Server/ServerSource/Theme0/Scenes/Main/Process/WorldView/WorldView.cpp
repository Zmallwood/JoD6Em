/*
 * WorldView.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "WorldView.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "Configuration/GameProperties.hpp"
#include "Theme0/Scenes/Main/MainSceneMath/TileGridMath.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/Mob.hpp"
#include "Theme0/Scenes/Main/Process/TileHovering.hpp"
#include "Theme0/Scenes/Main/Process/MobTargeting.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"

namespace JoD {
    void WorldView::Render(WebSocket &webSocket) const {
        auto tileHovering =
            std::static_pointer_cast<TileHovering>(m_mainScene.m_components.at(
                                                       MainSceneComponents::
                                                       TileHovering));
        auto mobTargeting =
            std::static_pointer_cast<MobTargeting>(m_mainScene.m_components.at(
                                                       MainSceneComponents::
                                                       MobTargeting));
        auto tileSize =
            CalculateTileSize(m_userConnection.GetAspectRatio());
        auto playerCoordinate =
            m_userConnection.m_player->m_coordinate;
        auto numGridRows = _<GameProperties>().k_numGridRows;
        auto numGridCols =
            CalculateNumGridCols(m_userConnection.GetAspectRatio());
        auto smallValue = 0.0001f;
        for (auto y = 0; y < numGridRows; y++){
            for (auto x = 0; x < numGridCols; x++){
                auto coordX = playerCoordinate.x -
                               (numGridCols - 1) / 2 + x;
                auto coordY = playerCoordinate.y -
                               (numGridRows - 1) / 2 + y;
                if (coordX < 0 || coordY < 0 || coordX >= 100 ||
                    coordY >= 100) continue;
                auto tile =
                    _<World>().m_currentWorldArea->m_tiles[coordX][
                        coordY];
                auto ground = tile->m_ground;
                if (ground == Hash("GroundWater")) {
                    auto animIndex =
                        ((std::chrono::high_resolution_clock::now().
                          time_since_epoch().count()/1000000)%1200)/400;
                    ground = Hash("GroundWater_" + std::to_string(animIndex));
                }
                m_userConnection.SendImageDrawInstruction(
                    webSocket,
                    ground,
                    {x * tileSize.w, y * tileSize.h,
                     tileSize.w + smallValue,
                     tileSize.h + smallValue});
                if (coordX ==
                    tileHovering->
                    m_hoveredCoordinate.x &&
                    coordY ==
                    tileHovering->
                    m_hoveredCoordinate.y){
                    m_userConnection.SendImageDrawInstruction(
                        webSocket,
                        "HoveredTile",
                        {x * tileSize.w, y * tileSize.h, tileSize.w,
                         tileSize.h});
                }
                if (tile->m_object) {
                    m_userConnection.SendImageDrawInstruction(
                        webSocket,
                        tile->m_object,
                        {x * tileSize.w, y * tileSize.h, tileSize.w,
                         tileSize.h});
                }
                if (tile->m_mob) {
                    if (tile->m_mob ==
                        mobTargeting->
                        m_targetedCreature){
                        m_userConnection.SendImageDrawInstruction(
                            webSocket,
                            "TargetedMob",
                            {x * tileSize.w, y * tileSize.h,
                             tileSize.w,
                             tileSize.h});
                    }
                    m_userConnection.SendImageDrawInstruction(
                        webSocket,
                        tile->m_mob->m_type,
                        {x * tileSize.w, y * tileSize.h, tileSize.w,
                         tileSize.h});
                    m_userConnection.SendTextDrawInstruction(
                        webSocket,
                        "Mob, Lvl." +
                        std::to_string(tile->m_mob->m_level),
                        {x*tileSize.w, (y - 0.5f)*tileSize.h});
                }
                if (coordX == playerCoordinate.x &&
                    coordY == playerCoordinate.y){
                    m_userConnection.SendImageDrawInstruction(
                        webSocket, "Player", {
                        x * tileSize.w, y * tileSize.h,
                        tileSize.w,
                        tileSize.h});
                }
            }
        }
    }
}
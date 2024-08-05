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
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "Process/RenderGround.hpp"
#include "Process/RenderTileSymbols.hpp"
#include "Process/RenderObjects.hpp"
#include "Process/RenderMobs.hpp"
#include "Process/RenderPlayer.hpp"

namespace JoD {
    
    void WorldView::Render(WebSocket &webSocket) const {
        
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
                auto tileBounds = RectF {x * tileSize.w, y * tileSize.h,
                                         tileSize.w + smallValue,
                                         tileSize.h + smallValue};
                RenderGround(m_userConnection, webSocket, tile, tileBounds);
                RenderTileSymbols(m_mainScene, m_userConnection, webSocket, {coordX, coordY}, tileBounds);
                RenderObjects(m_userConnection, webSocket, tile, tileBounds);
                RenderMobs(m_mainScene, m_userConnection, webSocket, tile, tileBounds);
                RenderPlayer(m_userConnection, webSocket, {coordX, coordY}, tileBounds);
            }
        }
    }
}
/*
 * TileHovering.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "TileHovering.hpp"
#include "Theme0/Scenes/Main/MainSceneMath/TileGridMath.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "Configuration/GameProperties.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.hpp"

namespace JoD {
    
    void TileHovering::Update(){
        
        const auto tileSize =
            CalculateTileSize(
                m_userConnection.m_userGameInstanceEngine->GetAspectRatio());
        
        const auto playerCoordinate =
            m_userConnection.m_userGameInstanceEngine->m_player->m_coordinate;
        
        const auto numRows = _<GameProperties>().k_numGridRows;
        const auto numCols =
            CalculateNumGridCols(
                m_userConnection.m_userGameInstanceEngine->GetAspectRatio());
        
        const auto tileX =
            playerCoordinate.x - (numCols - 1) / 2 +
            static_cast<int>(m_userConnection.m_userGameInstanceEngine->
                             m_mousePosition.x /
                             tileSize.w);
        
        const auto tileY =
            playerCoordinate.y - (numRows - 1) / 2 +
            static_cast<int>(m_userConnection.m_userGameInstanceEngine->
                             m_mousePosition.y /
                             tileSize.h);
        
        m_hoveredCoordinate = {tileX, tileY};
    }
}
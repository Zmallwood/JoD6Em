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
        
        auto tileSize =
            CalculateTileSize(m_userConnection.m_userGameInstanceEngine->GetAspectRatio());
        
        auto playerCoordinate = m_userConnection.m_userGameInstanceEngine->m_player->m_coordinate;
        
        auto numRows = _<GameProperties>().k_numGridRows;
        auto numCols = CalculateNumGridCols(m_userConnection.m_userGameInstanceEngine->GetAspectRatio());
        
        auto tileX =
            playerCoordinate.x - (numCols - 1) / 2 +
            static_cast<int>(m_userConnection.m_userGameInstanceEngine->m_mousePosition.x /
                             tileSize.w);
        
        auto tileY =
            playerCoordinate.y - (numRows - 1) / 2 +
            static_cast<int>(m_userConnection.m_userGameInstanceEngine->m_mousePosition.y /
                             tileSize.h);
        
        m_hoveredCoordinate = {tileX, tileY};
    }
}
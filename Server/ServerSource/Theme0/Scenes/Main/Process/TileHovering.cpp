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
#include "ServerCore/UserGameInstance/EngineInstance.hpp"

namespace JoD {
    
    void TileHovering::Update(UserID userID){
        
        const auto tileSize =
            CalculateTileSize(
                EngineInstance().GetAspectRatio());
        
        const auto playerCoordinate =
            EngineInstance().Player()->Coord();
        
        const auto numRows = _<GameProperties>().GetNumGridRows();
        const auto numCols =
            CalculateNumGridCols(
                EngineInstance().GetAspectRatio());
        
        const auto tileX =
            playerCoordinate.x - (numCols - 1) / 2 +
            static_cast<int>(EngineInstance().
                             MousePosition().x /
                             tileSize.w);
        
        const auto tileY =
            playerCoordinate.y - (numRows - 1) / 2 +
            static_cast<int>(EngineInstance().
                             MousePosition().y /
                             tileSize.h);
        
        m_hoveredCoordinate = {tileX, tileY};
    }
}
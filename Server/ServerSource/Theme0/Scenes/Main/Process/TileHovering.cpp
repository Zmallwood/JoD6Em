/*
 * TileHovering.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "TileHovering.hpp"
#include "Theme0/Scenes/Main/MainSceneMath/TileGridMath.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "Configuration/GameProperties.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
    
    void TileHovering::Update(UserID userID){
        
        const auto tileSize =
            CalculateTileSize(
                _<EngineGet>().GetAspectRatio(userID).value());
        
        const auto playerCoordinate =
            _<EngineGet>().GetPlayer(userID)->Coord();
        
        const auto numRows = _<GameProperties>().GetNumGridRows();
        const auto numCols =
            CalculateNumGridCols(
                _<EngineGet>().GetAspectRatio(userID).value());
        
        const auto tileX =
            playerCoordinate.x - (numCols - 1) / 2 +
            static_cast<int>(_<EngineGet>().
                             GetMousePosition(userID).value().x /
                             tileSize.w);
        
        const auto tileY =
            playerCoordinate.y - (numRows - 1) / 2 +
            static_cast<int>(_<EngineGet>().
                             GetMousePosition(userID).value().y /
                             tileSize.h);
        
        m_hoveredCoordinate = {tileX, tileY};
    }
}
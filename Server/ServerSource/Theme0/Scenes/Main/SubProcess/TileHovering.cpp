/*
 * TileHovering.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "TileHovering.hpp"
#include "Theme0/Scenes/Main/MainSceneMath/TileGridMath.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "Configuration/GameProperties.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
void TileHovering::Update(UserID userID) {
// Get tile size.
    auto tileSize = CalcTileSize(_<EngineGet>().GetAspectRatio(userID).value());
// Get player coordinate.
    auto playerCoord = _<EngineGet>().GetPlayer(userID)->GetCoord();
// Obtain tile grid columns and rows count.
    auto numRows = _<GameProperties>().GetNumGridRows();
    auto numCols = CalcNumGridCols(
        _<EngineGet>().GetAspectRatio(userID).value());
// Calculate the hovered tile coordinate components.
    auto tileX = playerCoord.x - (numCols - 1) / 2
                 + static_cast<int>(_<EngineGet>().GetMousePosition(
                                        userID).value().x / tileSize.w);
    auto tileY = playerCoord.y - (numRows - 1) / 2 +
                 static_cast<int>(_<EngineGet>().GetMousePosition(
                                      userID).value().y /
                                  tileSize.h);
// Combine the components into a Point and return.
    m_hoveredCoord = {tileX, tileY};
}
}
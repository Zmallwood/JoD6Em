/*
 * RenderTileSymbols.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderTileSymbols.hpp"
#include "Theme0/Scenes/Main/SubProcess/TileHovering.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
void RenderTileSymbols(UserID userID, Point coord, BoxF tileBounds) {
// Get main scene for the user.
    auto mainScene = _<EngineGet>().GetMainScene(userID);
// Get player object for user.    
    const auto &player = _<EngineGet>().GetPlayer(userID);
// Get tile hovering component.
    auto tileHovering =
        static_cast<TileHovering*>(
            mainScene->GetComponent(
                MainSceneComponents::
                TileHovering));
// Get hovered coordinate.
    auto hovCoord = tileHovering->GetHoveredCoord();
// If proper hovered coordinate was obtained
// and it equals the current coordinate.    
    if (hovCoord.has_value() && coord == hovCoord)
// Draw hovered tile image.
        UserSendDrawImage(userID, "HoveredTile", tileBounds);
// Get destination coordinate for player.
    auto destCoord = player->GetDestCoord();
// If proper destination coordinate was obtained
// and destination coordinate equals current coordinate.
    if (destCoord.has_value() && coord == destCoord)
// Draw destination symbol on ground.
        UserSendDrawImage(userID, "DestinationSymbol", tileBounds);
}
}
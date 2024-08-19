/*
 * RenderTileSymbols.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderTileSymbols.hpp"
#include "Theme0/Scenes/Main/SubProcess/TileHovering.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {

void RenderTileSymbols(
    const MainScene& mainScene,
    UserID userID,
    Point coordinate, BoxF tileBounds) {
    
    const auto &player = _<EngineGet>().GetPlayer(userID);
    
    auto tileHovering =
        static_cast<TileHovering*>(
            mainScene.GetComponent(
                MainSceneComponents::
                TileHovering));
    
    if (tileHovering->GetHoveredCoordinate().has_value() &&
        coordinate == tileHovering->GetHoveredCoordinate()){
        
        UserSendDrawImage(
            userID,
            "HoveredTile",
            tileBounds);
    }
    
    if (player->GetDestCoord().has_value() &&
        coordinate == player->GetDestCoord()) {
        
        UserSendDrawImage(
            userID,
            "DestinationSymbol",
            tileBounds);
    }
}

}
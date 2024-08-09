/*
 * RenderTileSymbols.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderTileSymbols.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "Theme0/Scenes/Main/Process/TileHovering.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/UserGameInstance/EngineInstance.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    
    void RenderTileSymbols(
        const MainScene& mainScene,
        const EngineInstance& engineInstance,
        WebSocket &webSocket,
        Point coordinate, BoxF tileBounds) {
        
        const auto &player = engineInstance.Player();
        
        auto tileHovering =
            static_cast<TileHovering*>(
                mainScene.GetComponent(
                    MainSceneComponents::
                    TileHovering));
        
        if (tileHovering->HoveredCoordinate().has_value() && coordinate == tileHovering->HoveredCoordinate()){
            
            SendImageDrawInstruction(
                webSocket,
                "HoveredTile",
                tileBounds);
        }
        
        if (player->DestCoord().has_value() &&
            coordinate == player->DestCoord()) {
            
            SendImageDrawInstruction(
                webSocket,
                "DestinationSymbol",
                tileBounds);
        }
    }
}
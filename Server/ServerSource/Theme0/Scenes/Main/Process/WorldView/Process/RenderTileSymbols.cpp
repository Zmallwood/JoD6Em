/*
 * RenderTileSymbols.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderTileSymbols.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "Theme0/Scenes/Main/Process/TileHovering.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    
    void RenderTileSymbols(
        const MainScene& mainScene,
        const UserGameInstanceEngine& userGameInstanceEngine,
        WebSocket &webSocket,
        Point coordinate, BoxF tileBounds) {
        
        const auto player = userGameInstanceEngine.m_player;
        
        const auto tileHovering =
            std::static_pointer_cast<TileHovering>(
                mainScene.m_components.at(
                    MainSceneComponents::
                    TileHovering));
        
        if (coordinate == tileHovering->m_hoveredCoordinate){
            
            SendImageDrawInstruction(
                webSocket,
                "HoveredTile",
                tileBounds);
        }
        
        if (player->m_destCoord.has_value() &&
            coordinate == player->m_destCoord) {
            
            SendImageDrawInstruction(
                webSocket,
                "DestinationSymbol",
                tileBounds);
        }
    }
}
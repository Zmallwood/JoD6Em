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
        const MainScene& mainScene, const UserConnection& userConnection,
        WebSocket &webSocket,
        Point coordinate, BoxF tileBounds) {
        
        const auto player = userConnection.m_userGameInstanceEngine->m_player;
        
        const auto tileHovering =
            std::static_pointer_cast<TileHovering>(
                mainScene.m_components.at(
                    MainSceneComponents::
                    TileHovering));
        
        if (coordinate.x ==
            tileHovering->
            m_hoveredCoordinate.x &&
            coordinate.y ==
            tileHovering->
            m_hoveredCoordinate.y){
            
            SendImageDrawInstruction(
                webSocket,
                "HoveredTile",
                tileBounds);
        }
        
        if (coordinate.x == player->m_destination.x &&
            coordinate.y == player->m_destination.y) {
            
            SendImageDrawInstruction(
                webSocket,
                "DestinationSymbol",
                tileBounds);
        }
    }
}
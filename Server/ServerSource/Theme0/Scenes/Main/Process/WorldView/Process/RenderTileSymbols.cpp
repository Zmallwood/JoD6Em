/*
 * RenderTileSymbols.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderTileSymbols.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "Theme0/Scenes/Main/Process/TileHovering.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"

namespace JoD {
    
    void RenderTileSymbols(
        MainScene& mainScene, UserConnection& userConnection,
        WebSocket &webSocket,
        Point coordinate, BoxF tileBounds) {
        
        auto tileHovering =
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
            
            userConnection.SendImageDrawInstruction(
                webSocket,
                "HoveredTile",
                tileBounds);
        }
    }
}
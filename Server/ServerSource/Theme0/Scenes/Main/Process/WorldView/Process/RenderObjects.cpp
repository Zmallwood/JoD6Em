/*
 * RenderObjects.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderObjects.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/Net/UserConnection.hpp"

namespace JoD {
    
    void RenderObjects(
        UserConnection& userConnection, WebSocket &webSocket,
        std::shared_ptr<Tile> tile, RectF tileBounds) {
        
        if (tile->m_object) {
            userConnection.SendImageDrawInstruction(
                webSocket,
                tile->m_object,
                tileBounds);
        }
    }
}
/*
 * RenderObjects.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderObjects.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/Object.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/ServerWide/AssetsInformation/ImageDimensions.hpp"

namespace JoD {
    
    void RenderObjects(
        UserConnection& userConnection, WebSocket &webSocket,
        std::shared_ptr<Tile> tile, BoxF tileBounds) {
        
        if (tile->m_object) {
            
            auto foundImageDim = false;
            Size imageDimensions;
            
            if (_<ImageDimensions>().m_dimensions.contains(tile->m_object->m_type)) {
                
                imageDimensions = _<ImageDimensions>().m_dimensions.at(tile->m_object->m_type);
                foundImageDim = true;
            }
            
            if (!foundImageDim) {
                
                userConnection.SendRequestImageDimensions(
                    webSocket,
                    tile->m_object->m_type);
                
                return;
            }
            
            auto width = imageDimensions.w/60.0f*tileBounds.w;
            auto height = imageDimensions.h/60.0f*tileBounds.h;
            
            auto newBounds = BoxF{tileBounds.x + tileBounds.w/2 - width/2,
                                   tileBounds.y + tileBounds.h - height, width, height};
            
            userConnection.SendImageDrawInstruction(
                webSocket,
                tile->m_object->m_type,
                newBounds);
        }
    }
}
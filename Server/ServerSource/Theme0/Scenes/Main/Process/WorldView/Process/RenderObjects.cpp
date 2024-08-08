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
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    
    void RenderObjects(
        WebSocket &webSocket,
        std::shared_ptr<const Tile> tile, BoxF tileBounds) {
        
        if (tile->m_object) {
            
            auto foundImageDim = false;
            Size imageDimensions;
            
            if (_<ImageDimensions>().m_dimensions.contains(tile->m_object->m_type)) {
                
                imageDimensions = _<ImageDimensions>().m_dimensions.at(tile->m_object->m_type);
                foundImageDim = true;
            }
            
            if (!foundImageDim) {
                
                SendRequestImageDimensions(
                    webSocket,
                    tile->m_object->m_type);
                
                return;
            }
            
            const auto width = imageDimensions.w/60.0f*tileBounds.w;
            const auto height = imageDimensions.h/60.0f*tileBounds.h;
            
            const auto newBounds = BoxF{tileBounds.x + tileBounds.w/2 - width/2,
                                   tileBounds.y + tileBounds.h - height, width, height};
            
            SendImageDrawInstruction(
                webSocket,
                tile->m_object->m_type,
                newBounds);
        }
    }
}
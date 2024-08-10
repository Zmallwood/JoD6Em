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
        Tile* tile, BoxF tileBounds) {
        
        if (tile->GetObject()) {
            
            auto foundImageDim = false;
            Size imageDimensions;
            
            auto dim = _<ImageDimensions>().GetDimension(tile->GetObject()->GetType());
            
            if (dim.has_value()) {
                
                imageDimensions = *dim;
                foundImageDim = true;
            }
            
            if (!foundImageDim) {
                
                SendRequestImageDimensions(
                    webSocket,
                    tile->GetObject()->GetType());
                
                return;
            }
            
            const auto width = imageDimensions.w/60.0f*tileBounds.w;
            const auto height = imageDimensions.h/60.0f*tileBounds.h;
            
            const auto newBounds = BoxF{tileBounds.x + tileBounds.w/2 - width/2,
                                   tileBounds.y + tileBounds.h - height, width, height};
            
            SendImageDrawInstruction(
                webSocket,
                tile->GetObject()->GetType(),
                newBounds);
        }
    }
}
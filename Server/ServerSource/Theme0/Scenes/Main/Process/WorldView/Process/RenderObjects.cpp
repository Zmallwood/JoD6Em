/*
 * RenderObjects.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderObjects.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/ServerWide/AssetsInformation/ImageDimensions.hpp"

namespace JoD {
    
    void RenderObjects(
        UserConnection& userConnection, WebSocket &webSocket,
        std::shared_ptr<Tile> tile, RectF tileBounds) {
        
        
        
        // std::cout << "SIZE2: " << g_imageDimensions.load().size() << std::endl;
        
        
        // std::cout << "Find: " << tile->m_object << std::endl;
        
        // for (auto entry : g_imageDimensions) {
        //     std::cout << "entry: " << entry.first << std::endl;
        // }
        
        if (tile->m_object) {
            auto foundImageDim = false;
            Size s;
            if (_<ImageDimensions>().m_dimensions.contains(tile->m_object)) {
                s = _<ImageDimensions>().m_dimensions.at(tile->m_object);
                foundImageDim = true;
            }
            
            if (!foundImageDim) {
                userConnection.SendRequestImageDimensions(
                    webSocket,
                    tile->m_object);
                return;
            }

            auto w = s.w/60.0f*tileBounds.w;
            auto h = s.h/60.0f*tileBounds.h;

            auto newBounds = RectF{tileBounds.x + tileBounds.w/2 - w/2, tileBounds.y + tileBounds.h - h, w, h};
                        
            userConnection.SendImageDrawInstruction(
                webSocket,
                tile->m_object,
                newBounds);
        }
    }
}
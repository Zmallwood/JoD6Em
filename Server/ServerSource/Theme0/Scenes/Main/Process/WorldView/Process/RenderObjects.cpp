/*
 * RenderObjects.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderObjects.hpp"
#include "Tile.hpp"
#include "Object.hpp"
#include "ObjectsPile.hpp"
#include "ServerCore/ServerWide/AssetsInformation/ImageDimensions.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    
    void RenderObjects(
        UserID userID,
        Tile* tile, BoxF tileBounds) {
        
        for (auto object : tile->GetObjectsPile().GetObjects()) {
            
            if (object) {
                
                auto foundImageDim = false;
                Size imageDimensions;
                
                auto dim =
                    _<ImageDimensions>().GetDimension(
                        object->GetType());
                
                if (dim.has_value()) {
                    
                    imageDimensions = *dim;
                    foundImageDim = true;
                }
                
                if (!foundImageDim) {
                    
                    SendRequestImageDimensions(
                        userID,
                        object->GetType());
                    
                    return;
                }
                
                const auto width = imageDimensions.w/60.0f*tileBounds.w;
                const auto height = imageDimensions.h/60.0f*tileBounds.h;
                
                const auto newBounds = BoxF{tileBounds.x + tileBounds.w/2 -
                                            width/2,
                                            tileBounds.y + tileBounds.h -
                                            height, width, height};
                
                SendImageDrawInstruction(
                    userID,
                    object->GetType(),
                    newBounds);
                
                if (object->GetContainedNPC()) {
                    
                SendImageDrawInstruction(
                    userID,
                    "NPC_Mounted",
                    newBounds);
                }
            }
        }
    }
}
/*
 * RenderNPCs.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderNPCs.hpp"
#include "Tile.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/AssetsInformation/ImageDimensions.hpp"

namespace JoD {
    
    void RenderNPCs(UserID userID, Tile* tile, BoxF tileBounds) {
        
        if (tile->GetNPC()) {
            
            auto foundImageDim = false;
            Size imageDimensions;
            
            auto dim = _<ImageDimensions>().GetDimension("Player");
            
            if (dim.has_value()) {
                
                imageDimensions = *dim;
                foundImageDim = true;
            }
            
            if (!foundImageDim) {
                
                SendRequestImageDimensions(
                    userID,
                    "NPC");
                
                return;
            }
            
            const auto width = imageDimensions.w/60.0f*tileBounds.w;
            const auto height = imageDimensions.h/60.0f*tileBounds.h;
            
            const auto newBounds = BoxF{tileBounds.x + tileBounds.w/2 - width/2,
                                        tileBounds.y + tileBounds.h/2 - height,
                                        width, height};
            
            SendImageDrawInstruction(
                userID,
                "NPC",
                newBounds);
        }
    }
}

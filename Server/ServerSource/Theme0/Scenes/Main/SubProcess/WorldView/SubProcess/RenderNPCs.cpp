/*
 * RenderNPCs.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderNPCs.hpp"
#include "Tile.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/AssetsInformation/ImageDimensions.hpp"

namespace JoD {

void RenderNPCs(UserID userID, Tile* tile, BoxF tileBounds) {
    
// Check if tile has NPC positioned on it.
    if (tile->GetNPC()) {

// To hold data after trying to look up image dimensions.
        
        auto foundImageDim = false;
        Size imageDimensions;
        
// Try get dimension for NPC-image.
        auto dim = _<ImageDimensions>().GetDimension("NPC");
        
// If proper dimenions data were obtained...
        if (dim.has_value()) {
            
// We can use these dimensions.
            imageDimensions = *dim;
            foundImageDim = true;
        }
        
// If no proper image dimensions were obtained.
        if (!foundImageDim) {
            
// Request dimensions for the NPC image from the user.
            UserSendReqImageDimensions(userID, "NPC");

// Cancel drawing since we lack image dimensions.
            return;
        }
        
// Calculate the image dimensions with format for the canvas.
        auto width = imageDimensions.w/60.0f*tileBounds.w;
        auto height = imageDimensions.h/60.0f*tileBounds.h;
        
// Create the bounds for the image.
        auto newBounds = BoxF{tileBounds.x + tileBounds.w/2 - width/2,
                              tileBounds.y + tileBounds.h/2 - height,
                              width, height};
        
// Draw the NPC image.
        UserSendDrawImage(userID, "NPC", newBounds);
    }
}

}

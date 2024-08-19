/*
 * RenderObjects.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderObjects.hpp"
#include "Tile.hpp"
#include "Object.hpp"
#include "ObjectsPile.hpp"
#include "ServerCore/ServerWide/AssetsInformation/ImageDimensions.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {

void RenderObjects(UserID userID, Tile* tile, BoxF tileBounds) {
    
// Loop over all objects located on tile.
    for (auto object : tile->GetObjectsPile().GetObjects()) {
        
// To hold information from looking up image dimensions for object image.
        auto foundImageDim = false;
        Size imageDimensions;
        
// Can contain image dimensions or std::nullopt value.
        auto dim =
            _<ImageDimensions>().GetDimension(object->GetType());
        
// If propert image dimensions were obtained.
        if (dim.has_value()) {
            
// Use them.
            imageDimensions = *dim;
            foundImageDim = true;
        }
        
// If no proper image dimensions were obtained.
        if (!foundImageDim) {
            
// Request image dimensions from user.
            UserSendReqImageDimensions(userID, object->GetType());
            
// Cancel drawing since we lack image dimensions.
            return;
        }
        
// Convert image dimensions to format for canvas.
        auto width = imageDimensions.w/60.0f*tileBounds.w;
        auto height = imageDimensions.h/60.0f*tileBounds.h;
        
// Create the bounds of the image to be drawn.
        auto newBounds = BoxF{tileBounds.x + tileBounds.w/2 -
                              width/2,
                              tileBounds.y + tileBounds.h -
                              height, width, height};
        
// Draw the object image.
        UserSendDrawImage(userID, object->GetType(), newBounds);
        
// Check if object containes an NPC, such as an NPC located in a vehicle.
        if (object->GetContainedNPC()) {
            
// Draw a mounted NPC on top of the object image.
            UserSendDrawImage(userID, "NPC_Mounted", newBounds);
        }
    }
}

}
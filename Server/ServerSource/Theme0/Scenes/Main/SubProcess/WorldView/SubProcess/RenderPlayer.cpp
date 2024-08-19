/*
 * RenderPlayer.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderPlayer.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/ServerWide/AssetsInformation/ImageDimensions.hpp"

namespace JoD {

void RenderPlayer(UserID userID, Point coord, BoxF tileBounds) {
    
// Get player coordinate.
    auto playerCoord = _<EngineGet>().GetPlayer(userID)->GetCoord();
    
// If considered coordinate equals the players coordinate.
    if (coord == playerCoord){
        
// To hold information from looking up image dimensions.
        auto foundImageDim = false;
        Size imageDimensions;
        
// Contains image dimensions or std::nullopt value.
        auto dim = _<ImageDimensions>().GetDimension("Player");
        
// If proper image dimensions were obtained.
        if (dim.has_value()) {
            
// Use them.
            imageDimensions = *dim;
            foundImageDim = true;
        }
        
// If proper image dimensions were not obtained.
        if (!foundImageDim) {
            
// Request image dimensions from user.
            UserSendReqImageDimensions(userID, "Player");
            
// Cancel drawing since we lack image dimensions.
            return;
        }
        
// Convert image dimensions to format for canvas.
        auto width = imageDimensions.w/60.0f*tileBounds.w;
        auto height = imageDimensions.h/60.0f*tileBounds.h;
        
// Create bounds for drawing the image.
        auto newBounds = BoxF {
            tileBounds.x + tileBounds.w/2 - width/2,
            tileBounds.y + tileBounds.h/2 - height,
            width, height};
        
// Draw player image.
        UserSendDrawImage(userID, "Player", newBounds);
    }
}

}
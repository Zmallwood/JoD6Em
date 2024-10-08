/*
 * RenderGround.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderGround.hpp"
#include "Tile.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
void RenderGround(
    UserID userID, Tile* tile, BoxF tileBounds, Tile* tileW, Tile* tileN,
    int playerElev, Point coord) {
// Get elevation of tile.
    auto elev = tile->GetElevation();
// Loop from the bottom up to elevation level.
    for (auto i = 0; i < elev; i++) {
// Create bounds for bottom elevation image.
        auto boundsElevS = BoxF {tileBounds.x - tileBounds.w*0.25f,
                                 tileBounds.y, tileBounds.w*1.25f,
                                 tileBounds.h};
// Create bounds for right elevation image.
        auto boundsElevE = BoxF {tileBounds.x,
                                 tileBounds.y - tileBounds.h*0.25f,
                                 tileBounds.w, tileBounds.h*1.25f};
// Draw bottom elevation image.
        UserSendDrawImage(userID, "ElevationS", boundsElevS);
// Draw right elevation image.
        UserSendDrawImage(userID, "ElevationE", boundsElevE);
// Move the tile bounds every elevation step.
        tileBounds.x -= tileBounds.w/8;
        tileBounds.y -= tileBounds.h/4;
    }
    auto ground = tile->GetGround();
// If ground is water, perform animation logic.
    if (ground == Hash("GroundWater")) {
// Calculate animation frame index based on time.
        auto animFrameIdx =
            (((Now().time_since_epoch().count()/1000000) + 6*coord.x*coord.y)%
             1200)/400;
// Change the ground image hash code to an animated one.
        ground = Hash("GroundWater_" + std::to_string(animFrameIdx));
    }
// Do the actual ground drawing.
    UserSendDrawImage(userID, ground, tileBounds);
// If ground is of water type.
    if (tile->GetGround() == Hash("GroundWater")) {
// If west neighbour tile is not water.
        if (tileW && tileW->GetGround() != Hash("GroundWater")) {
// Draw tile edge to the west.
            UserSendDrawImage(userID, "EdgeW", tileBounds);
        }
// If north neighbour tile is not water.
        if (tileN && tileN->GetGround() != Hash("GroundWater")) {
// Draw tile edge to the north.
            UserSendDrawImage(userID, "EdgeN", tileBounds);
        }
    }
// If tile is not water.
    else {
// If west tile is water.
        if (tileW && tileW->GetGround() == Hash("GroundWater")) {
// Draw tile edge to the west.
            UserSendDrawImage(userID, "EdgeW", tileBounds);
        }
// If north tile is water.
        if (tileN && tileN->GetGround() == Hash("GroundWater")) {
// Draw tile edge to the north.
            UserSendDrawImage(userID, "EdgeN", tileBounds);
        }
    }
// If west tile is valid.
    if (tileW) {
// If west tile elevation is lower than current tiles elevation.
        if (tileW->GetElevation() < tile->GetElevation()) {
// Draw tile edge to the west.
            UserSendDrawImage(userID, "EdgeW", tileBounds);
        }
    }
// Of north tile is valid.
    if (tileN) {
// If north tile elevation is lower than current tiles elevation.
        if (tileN->GetElevation() < tile->GetElevation()) {
// Draw tile edge to the north.
            UserSendDrawImage(userID, "EdgeN", tileBounds);
        }
    }
    
    
    auto above = tile->GetAbove();
    
    if (above) {
        tileBounds.x -= tileBounds.w;
        tileBounds.y -= 2*tileBounds.h;
        
        auto elev = tile->GetElevation();
        for (auto i = 0; i < elev; i++) {
            tileBounds.x += tileBounds.w/8;
            tileBounds.y += tileBounds.h/4;
        }
        
        tile = above;
        
        tileW = tileW->GetAbove();
        tileN = tileN->GetAbove();
        
        auto ground = tile->GetGround();
// If ground is water, perform animation logic.
        if (ground == Hash("GroundWater")) {
// Calculate animation frame index based on time.
            auto animFrameIdx =
                (((Now().time_since_epoch().count()/1000000) + 6*coord.x*
                  coord.y)%1200)/400;
// Change the ground image hash code to an animated one.
            ground = Hash("GroundWater_" + std::to_string(animFrameIdx));
        }
        if (ground)
            UserSendDrawImage(userID, ground, tileBounds);
        
        if (ground && (!tileW || !tileW->GetGround())) {
            UserSendDrawImage(userID, "EdgeW", tileBounds);
        }
        if (ground && (!tileN || !tileN->GetGround())) {
            UserSendDrawImage(userID, "EdgeN", tileBounds);
        }
        if (!ground && (tileW && tileW->GetGround())) {
            UserSendDrawImage(userID, "EdgeW", tileBounds);
        }
        if (!ground && (tileN && tileN->GetGround())) {
            UserSendDrawImage(userID, "EdgeN", tileBounds);
        }
        
    }
    else {
        if (tileW && tileW->GetAbove() && tileW->GetAbove()->GetGround()) {
            auto tileBoundsW = tileBounds;
            tileBoundsW.x -= tileBoundsW.w;
            tileBoundsW.y -= 2*tileBoundsW.h;
            
            UserSendDrawImage(userID, "EdgeW", tileBoundsW);
        }
        
        if (tileN && tileN->GetAbove() && tileN->GetAbove()->GetGround()) {
            auto tileBoundsN = tileBounds;
            tileBoundsN.x -= tileBoundsN.w;
            tileBoundsN.y -= 2*tileBoundsN.h;
            
            UserSendDrawImage(userID, "EdgeN", tileBoundsN);
        }
    }
}
}
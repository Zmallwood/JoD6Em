/*
 * RenderPlayer.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class Tile;

///
/// Renders player on tile in the world view if player object is
/// located on the tile with provided coords.
///
/// @param userID User ID for user which player characters is drawn.
/// @param coord Coordinate of tile the function is called for.
/// @param tileBounds Bounds area of tile the function is called for.
///
void RenderPlayer(UserID userID, Point coord, BoxF tileBounds);
    
}
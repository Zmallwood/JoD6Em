/*
 * RenderGround.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
class Tile;

/// Renders ground in the world view.
/// @param webSocket Web socket object associated with user.
/// @param tile Tile of which ground should be rendered.
/// @param tileBounds Bounds area of the tile which ground is to be rendered.
/// @param tileW West neighbour tile.
/// @param tileN North neighbour tile.
/// @param playerElev Elevation of the tile the player is located at.
void RenderGround(
    UserID userID, Tile* tile, BoxF tileBounds, Tile* tileW, Tile* tileN,
    int playerElev, Point coord);
}
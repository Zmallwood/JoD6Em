/*
 * RenderCreatures.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
class Tile;

/// Renders a mob, if there is one, of a tile in the world view.
/// @param webSocket Web socker associated with the user.
/// @param tile Tile of which mob is to be rendered.
/// @param tileBounds Bounds area of the tile, which mob is to be rendered.
void RenderCreatures(UserID userID, Tile* tile, BoxF tileBounds);
}
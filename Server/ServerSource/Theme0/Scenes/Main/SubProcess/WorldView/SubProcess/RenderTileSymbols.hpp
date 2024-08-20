/*
 * RenderTileSymbols.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
/// Renders symbols on tile in the world view.
/// @param userID User ID for user which we are rendering tile symbols for.
/// @param coord Coordinate for the tile for which the function is called.
/// @param tileBounds Bounds area of tile for which the function is called.
void RenderTileSymbols(UserID userID, Point coord, BoxF tileBounds);
}
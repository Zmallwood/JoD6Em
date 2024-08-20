/*
 * TileGridMath.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "TileGridMath.hpp"
#include "Configuration/GameProperties.hpp"

namespace JoD {
SizeF CalcTileSize(float aspectRatio) {
// Get tile height.
    const auto tileHeight = 1.0f / _<GameProperties>().GetNumGridRows();
// Calculate tile width from tile height and aspect ratio.
    const auto tileWidth = tileHeight / aspectRatio;
// Return results.
    return {tileWidth, tileHeight};
}

int CalcNumGridCols(float aspectRatio) {
// Get tile size.
    const auto tileSize = CalcTileSize(aspectRatio);
// Calculate number of grid columns by using the tile width.
    return static_cast<int>(1.0f/tileSize.w);
}
}
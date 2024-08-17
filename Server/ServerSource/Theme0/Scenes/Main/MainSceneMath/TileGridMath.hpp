/*
 * TileGridMath.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Calculates tile size based on amount of grid rows in tile grid.
///
/// @param aspectRatio Aspect ratio of canvas.
/// @return SizeF Tile size.
///
SizeF CalculateTileSize(float aspectRatio);

///
/// Calculates number of columns in the grid,
/// based on tile size and its related parameters.
///
/// @param aspectRatio Aspect ratio of canvas.
/// @return int Number of tile grid columns.
///
int CalculateNumGridCols(float aspectRatio);

}
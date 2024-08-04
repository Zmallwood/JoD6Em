/*
 * TileGridMath.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    SizeF CalculateTileSize(float aspect_ratio);
    int CalculateNumGridCols(float aspectRatio);
}
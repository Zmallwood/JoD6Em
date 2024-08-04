/*
 * TileGridMath.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "TileGridMath.h"
#include "Configuration/GameProperties.h"

namespace JoD {
    SizeF
    CalculateTileSize(float aspect_ratio){
        auto tile_height = 1.0f / _<GameProperties>().k_num_grid_rows;
        auto tile_width = tile_height / aspect_ratio;
        return {tile_width, tile_height};
    }

    int CalculateNumGridCols(float aspectRatio) {
        auto tileSize = CalculateTileSize(aspectRatio);
        return static_cast<int>(1.0f/tileSize.w);
    }
}
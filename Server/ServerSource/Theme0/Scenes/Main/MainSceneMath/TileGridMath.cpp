/*
 * TileGridMath.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "TileGridMath.h"
#include "Configuration/GameProperties.h"

namespace jod {
    sizef
    calculate_tile_size(float aspect_ratio){
        auto tile_height = 1.0f / _<game_properties>().k_num_grid_rows;
        auto tile_width = tile_height / aspect_ratio;
        return {tile_width, tile_height};
    }
}
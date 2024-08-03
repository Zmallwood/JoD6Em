/*
 * tile_grid_math.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "tile_grid_math.h"
#include "Configuration/game_properties.h"

namespace jod {
    sizef
    calculate_tile_size(float aspect_ratio){
        auto tile_height = 1.0f / _<game_properties>().k_num_grid_rows;
        auto tile_width = tile_height / aspect_ratio;
        return {tile_width, tile_height};
    }
}
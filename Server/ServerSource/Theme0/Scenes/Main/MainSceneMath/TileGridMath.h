/*
 * TileGridMath.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    sizef calculate_tile_size(float aspect_ratio);
    int calculate_num_grid_cols(float aspectRatio);
}
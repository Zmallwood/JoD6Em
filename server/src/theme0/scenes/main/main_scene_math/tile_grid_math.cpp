// tile_grid_math.cpp
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
///////////////////////////////////////////////////////////

#include "tile_grid_math.h"
#include "configuration/game_properties.h"

namespace jod {
    sizef
    calc_tile_size(float aspectRatio){
        auto tileHeight = 1.0f / _<game_properties>().numGridRows;
        auto tileWidth = tileHeight / aspectRatio;
        return {tileWidth, tileHeight};
    }
}
// Copyright (c) 2024 Andreas Åkerberg.
#include "math.h"
#include "configuration.h"

namespace jod {
    SizeF
    calc_tile_size(float aspectRatio){
        auto tileHeight = 1.0f / _<game_properties>().numGridRows;
        auto tileWidth = tileHeight / aspectRatio;
        return {tileWidth, tileHeight};
    }
}
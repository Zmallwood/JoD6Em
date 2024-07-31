// Copyright (c) 2024 Andreas Åkerberg.
#include "math.h"
#include "configuration.h"

namespace jod {
    SizeF
    CalcTileSize(float aspectRatio){
        auto tileHeight = 1.0f / _<GameProperties>().numGridRows;
        auto tileWidth = tileHeight / aspectRatio;
        return {tileWidth, tileHeight};
    }
}
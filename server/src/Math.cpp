// Copyright (c) 2024 Andreas Åkerberg.

#include "Math.h"

#include "Configuration.h"

namespace jod
{
    SizeF CalcTileSize(float aspectRatio)
    {
        auto tileHeight = 1.0f / _<GameProperties>().numGridRows;
        auto tileWidth = tileHeight / aspectRatio;

        return {tileWidth, tileHeight};
    }
}
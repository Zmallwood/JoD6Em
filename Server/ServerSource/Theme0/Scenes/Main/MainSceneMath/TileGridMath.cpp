/*
 * TileGridMath.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "TileGridMath.hpp"
#include "Configuration/GameProperties.hpp"

namespace JoD {
    
    SizeF CalculateTileSize(float aspectRatio){
        
        auto tileHeight = 1.0f / _<GameProperties>().k_numGridRows;
        auto tileWidth = tileHeight / aspectRatio;
        
        return {tileWidth, tileHeight};
    }
    
    int CalculateNumGridCols(float aspectRatio) {
        
        auto tileSize = CalculateTileSize(aspectRatio);
        
        return static_cast<int>(1.0f/tileSize.w);
    }
}
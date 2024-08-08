/*
 * TileGridMath.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "TileGridMath.hpp"
#include "Configuration/GameProperties.hpp"

namespace JoD {
    
    SizeF CalculateTileSize(float aspectRatio){
        
        const auto tileHeight = 1.0f / _<GameProperties>().GetNumGridRows();
        const auto tileWidth = tileHeight / aspectRatio;
        
        return {tileWidth, tileHeight};
    }
    
    int CalculateNumGridCols(float aspectRatio) {
        
        const auto tileSize = CalculateTileSize(aspectRatio);
        
        return static_cast<int>(1.0f/tileSize.w);
    }
}
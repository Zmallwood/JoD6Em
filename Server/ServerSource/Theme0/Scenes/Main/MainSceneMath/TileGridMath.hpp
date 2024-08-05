/*
 * TileGridMath.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    SizeF CalculateTileSize(float aspectRatio);
    
    int CalculateNumGridCols(float aspectRatio);
}
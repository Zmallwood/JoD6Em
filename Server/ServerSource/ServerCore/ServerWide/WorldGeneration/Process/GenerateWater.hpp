/*
 * GenerateWater.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class WorldArea;
    
    ///
    /// Generates water on a world area.
    /// 
    /// @param worldArea World area to generate water on.
    ///
    void GenerateWater(WorldArea* worldArea);
}
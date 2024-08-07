/*
 * GenerateRoads.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class WorldArea;
    
    ///
    /// Generates roads on a world area.
    /// 
    /// @param worldArea World area to generate roads on.
    ///
    void GenerateRoads(const std::unique_ptr<WorldArea> &worldArea);
}
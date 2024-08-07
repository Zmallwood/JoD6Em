/*
 * GenerateMobs.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class WorldArea;
    
    ///
    /// Generates different kind of mobs on a world area.
    /// 
    /// @param worldArea World area to generate mobs on.
    ///
    void GenerateMobs(const std::unique_ptr<WorldArea> &worldArea);
}
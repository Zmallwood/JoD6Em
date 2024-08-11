/*
 * GenerateCreatures.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class WorldArea;
    
    ///
    /// Generates different kind of creatures on a world area.
    /// 
    /// @param worldArea World area to generate creatures on.
    ///
    void GenerateCreatures(WorldArea* worldArea);
}
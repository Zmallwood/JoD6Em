/*
 * GenerateObjects.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class WorldArea;
    
    ///
    /// Generates different kind of objects to a world area.
    /// 
    /// @param worldArea World area to generate objects on.
    ///
    void GenerateObjects(const std::unique_ptr<WorldArea> &worldArea);
}
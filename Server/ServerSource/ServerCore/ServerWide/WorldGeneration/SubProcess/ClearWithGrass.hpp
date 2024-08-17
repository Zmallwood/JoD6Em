/*
 * ClearWithGrass.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class WorldArea;
    
    ///
    /// Clears a world area with grass as ground.
    ///
    /// @param worldArea World area to clear.
    ///
    void ClearWithGrass(WorldArea* worldArea);
}
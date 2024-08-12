/*
 * RenderObjects.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class Tile;
    
    ///
    /// Renders objects of a tile in the world view.
    /// 
    /// @param webSocket Web socket object associated with the user.
    /// @param tile Tile of which objects are to be rendered.
    /// @param tileBounds Bounds area of tile of which objects are to be rendered.
    ///
    void RenderObjects(
        UserID userID,
        Tile* tile, BoxF tileBounds);
}
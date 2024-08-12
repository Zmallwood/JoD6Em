/*
 * RenderPlayer.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class EngineInstance;
    class Tile;
    
    ///
    /// Renders player on tile in the world view if player object is
    /// located on the tile with provided coords.
    /// 
    /// @param engineInstance User game instance engine object associated with user.
    /// @param webSocket Web socket object associated with user.
    /// @param coordinate Coordinate of tile the function is called for.
    /// @param tileBounds Bounds area of tile the function is called for.
    ///
    void RenderPlayer(
        UserID userID,
        Point coordinate, BoxF tileBounds);
}
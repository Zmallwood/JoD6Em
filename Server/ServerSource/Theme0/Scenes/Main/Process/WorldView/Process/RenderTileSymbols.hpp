/*
 * RenderTileSymbols.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class MainScene;
    class EngineInstance;
    
    ///
    /// Renders symbols on tile in the world view.
    /// 
    /// @param mainScene Main scene associated with user.
    /// @param engineInstance User game instance engine associated with user.
    /// @param webSocket Web socket associated with user.
    /// @param coordinate Coordinate for the tile for which the function is called.
    /// @param tileBounds Bounds area of tile for which the function is called.
    ///
    void RenderTileSymbols(
        const MainScene& mainScene, UserID userID,
        WebSocket &webSocket,
        Point coordinate, BoxF tileBounds);
}
/*
 * RenderTileSymbols.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class MainScene;
    class UserConnection;
    
    ///
    /// Renders symbols on tile in the world view.
    /// 
    /// @param mainScene Main scene associated with user.
    /// @param userConnection User connection associated with user.
    /// @param webSocket Web socket associated with user.
    /// @param coordinate Coordinate for the tile for which the function is called.
    /// @param tileBounds Bounds area of tile for which the function is called.
    ///
    void RenderTileSymbols(
        const MainScene& mainScene, const UserConnection& userConnection,
        WebSocket &webSocket,
        Point coordinate, BoxF tileBounds);
}
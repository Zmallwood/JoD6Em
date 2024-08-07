/*
 * RenderGround.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class UserConnection;
    class Tile;
    
    ///
    /// Renders ground in the world view.
    /// 
    /// @param userConnection User connection associated with user.
    /// @param webSocket Web socket object associated with user.
    /// @param tile Tile of which ground should be rendered.
    /// @param tileBounds Bounds area of the tile which ground is to be rendered.
    ///
    void RenderGround(
        const UserConnection& userConnection, WebSocket &webSocket,
        std::shared_ptr<const Tile> tile, BoxF tileBounds);
}
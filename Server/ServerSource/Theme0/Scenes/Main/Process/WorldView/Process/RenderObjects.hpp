/*
 * RenderObjects.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class UserConnection;
    class Tile;
    
    ///
    /// Renders objects of a tile in the world view.
    /// 
    /// @param userConnection User connection associated with the user.
    /// @param webSocket Web socket object associated with the user.
    /// @param tile Tile of which objects are to be rendered.
    /// @param tileBounds Bounds area of tile of which objects are to be rendered.
    ///
    void RenderObjects(
        const UserConnection& userConnection, WebSocket &webSocket,
        std::shared_ptr<const Tile> tile, BoxF tileBounds);
}
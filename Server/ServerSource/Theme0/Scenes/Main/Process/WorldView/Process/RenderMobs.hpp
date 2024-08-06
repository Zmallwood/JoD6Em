/*
 * RenderMobs.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class MainScene;
    class UserConnection;
    class Tile;
    
    ///
    /// Renders a mob, if there is one, of a tile in the world view.
    /// 
    /// @param mainScene Main scene assocated with the user.
    /// @param userConnection User connection associated with the user.
    /// @param webSocket Web socker associated with the user.
    /// @param tile Tile of which mob is to be rendered.
    /// @param tileBounds Bounds area of the tile, which mob is to be rendered.
    ///
    void RenderMobs(
        MainScene& mainScene, UserConnection& userConnection,
        WebSocket &webSocket,
        std::shared_ptr<Tile> tile, BoxF tileBounds);
}
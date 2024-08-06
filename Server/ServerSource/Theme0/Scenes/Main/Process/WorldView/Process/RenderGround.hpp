/*
 * RenderGround.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class UserConnection;
    class Tile;
    
    void RenderGround(
        UserConnection& userConnection, WebSocket &webSocket,
        std::shared_ptr<Tile> tile, BoxF tileBounds);
}
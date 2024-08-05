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
    
    void RenderMobs(
        MainScene& mainScene, UserConnection& userConnection,
        WebSocket &webSocket,
        std::shared_ptr<Tile> tile, RectF tileBounds);
}
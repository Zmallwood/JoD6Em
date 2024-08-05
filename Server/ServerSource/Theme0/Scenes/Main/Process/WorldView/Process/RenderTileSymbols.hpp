/*
 * RenderTileSymbols.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class MainScene;
    
    class UserConnection;
    
    void RenderTileSymbols(
        MainScene& mainScene, UserConnection& userConnection,
        WebSocket &webSocket,
        Point coordinate, RectF tileBounds);
}
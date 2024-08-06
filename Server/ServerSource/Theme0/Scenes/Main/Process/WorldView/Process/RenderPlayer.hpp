/*
 * RenderPlayer.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class UserConnection;
    class Tile;
    
    void RenderPlayer(
        UserConnection& userConnection, WebSocket &webSocket,
        Point coordinate, BoxF tileBounds);
}
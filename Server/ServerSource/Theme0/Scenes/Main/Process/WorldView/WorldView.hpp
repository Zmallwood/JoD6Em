/*
 * WorldView.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class UserConnection;
    
    class WorldView {
    public:
        WorldView(UserConnection& userConnection);
        
        void Render(WebSocket &webSocket);
        
    private:
        UserConnection& m_userConnection;
    };
}
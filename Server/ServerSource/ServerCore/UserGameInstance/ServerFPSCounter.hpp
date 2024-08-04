/*
 * FPSCounter.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class UserConnection;
    
    class ServerFPSCounter {
    public:
        ServerFPSCounter(UserConnection& user_connection);
        
        void Update();
        
        void Render(WebSocket& ws);
        
    private:
        int m_fps = 0;
        int m_frames_count = 0;
        TimePoint m_ticks_last_update = Now();
        UserConnection& m_user_connection;
    };
}
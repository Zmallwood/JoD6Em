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
        ServerFPSCounter(UserConnection& userConnection);
        
        void Update();
        
        void Render(WebSocket& ws) const;
        
      private:
        int m_fps {0};
        
        int m_framesCount {0};
        
        TimePoint m_ticksLastUpdate {Now()};
        
        UserConnection& m_userConnection;
    };
}
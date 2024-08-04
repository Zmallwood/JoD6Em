/*
 * UserGameInstanceEngine.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */


#pragma once

namespace JoD {
    class UserConnection;
    class MouseInput;
    class SceneManager;
    class ServerFPSCounter;
    
    class UserGameInstanceEngine {
      public:
        UserGameInstanceEngine(UserConnection &userConnection);
        
        void Update();
        
        void Render(WebSocket &ws) const;
        
        std::shared_ptr<MouseInput> m_mouseInput;
        
        std::shared_ptr<SceneManager> m_sceneManager;
        
      private:
        std::shared_ptr<ServerFPSCounter> m_serverFPSCounter;
        
        UserConnection &m_userConnection;
    };
}
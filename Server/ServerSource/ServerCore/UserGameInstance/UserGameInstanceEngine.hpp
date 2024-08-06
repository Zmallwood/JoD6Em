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
    class Player;
    class Cursor;
    
    class UserGameInstanceEngine {
        
      public:
        UserGameInstanceEngine(UserConnection &userConnection);
        
        void Update();
        
        void Render(WebSocket &ws) const;
        
        float GetAspectRatio() const;
        
        PointF m_mousePosition;
        Size m_canvasSize;
        std::shared_ptr<MouseInput> m_mouseInput;
        std::shared_ptr<SceneManager> m_sceneManager;
        std::shared_ptr<Player> m_player;
        std::shared_ptr<Cursor> m_cursor;
        
      private:
        std::shared_ptr<ServerFPSCounter> m_serverFPSCounter;
        UserConnection &m_userConnection;
    };
}
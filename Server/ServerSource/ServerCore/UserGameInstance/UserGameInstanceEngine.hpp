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
        UserGameInstanceEngine(UserConnection &user_connection);
        
        void Update();
        
        void Render(WebSocket &ws);
        
        std::shared_ptr<MouseInput> m_mouse_input;
        
        std::shared_ptr<SceneManager> m_scene_manager;
        
    private:
        std::shared_ptr<ServerFPSCounter> m_server_fps_counter;
        
        UserConnection &m_user_connection;
    };
}
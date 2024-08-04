/*
 * SceneManager.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class UserConnection;
    class IScene;
    
    class SceneManager {
    public:
        SceneManager(UserConnection &user_connection);
        
        void UpdateCurrentScene();
        
        void RenderCurrentScene(WebSocket &ws);
        
        void GoTo(std::string_view scene_name);
        
    private:
        void AddScene(std::string_view sceneName, std::shared_ptr<IScene> scene);
        
        int m_current_scene = 0;
        
        std::map<int, std::shared_ptr<IScene>> m_scenes;
        
        UserConnection &m_user_connection;
    };
}
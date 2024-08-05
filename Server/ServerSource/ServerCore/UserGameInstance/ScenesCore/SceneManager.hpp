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
        SceneManager(UserConnection &userConnection);
        
        void UpdateCurrentScene();
        
        void RenderCurrentScene(WebSocket &ws) const;
        
        void GoTo(std::string_view sceneName);
        
      private:
        void AddScene(std::string_view sceneName,
                      std::shared_ptr<IScene> scene);
        
        int m_currentScene {0};
        
        std::map<int, std::shared_ptr<IScene>> m_scenes;
        
        UserConnection &m_userConnection;
    };
}
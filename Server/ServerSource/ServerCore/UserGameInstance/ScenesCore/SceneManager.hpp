/*
 * SceneManager.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "IScene.hpp"

namespace JoD {
    
    class EngineInstance;
    
    ///
    /// One instance is created for every connecting user. Initializes,
    /// processes and navigates between all scenes used in the game.
    ///
    class SceneManager {
        
      public:
        ///
        /// Construct a new Scene Manager object by initializing all scenes,
        /// and entering the IntroScene.
        ///
        /// @param userConnection User connection reference forwarding.
        ///
        SceneManager(EngineInstance &engineInstance);
        
        ///
        /// Updates the scene currently being presented.
        ///
        void UpdateCurrentScene(UserID userID);
        
        ///
        /// Renders the scene currently being presented.
        ///
        /// @param webSocket Web socket object for the current user.
        ///
        void RenderCurrentScene(UserID userID, WebSocket &webSocket) const;
        
        ///
        /// Move from the currently presented scene to another one.
        ///
        /// @param sceneName Name of the scene to go to.
        ///
        void GoToScene(std::string_view sceneName);
        
        template<class T>
        const T* GetScene(
            std::string_view sceneName) const {
            
            auto hashCode = Hash(sceneName);
            
            if (m_scenes.contains(hashCode)) {
                
                return static_cast<T*>(m_scenes.at(hashCode).get());
            }
            
            return nullptr;
        }
        
      private:
        ///
        /// Add a new scene, used in the ctor.
        ///
        /// @param sceneName Name of the scene to add.
        /// @param scene The scene object to add.
        ///
        void AddScene(std::string_view sceneName,
                      std::unique_ptr<IScene> scene);
        
        int m_currentScene {0}; ///< Hash code of name of the currently presented scene.
        std::map<int, std::unique_ptr<IScene>> m_scenes; ///< All scenes that has been added in ctor.
        EngineInstance &m_engineInstance; ///< User connection reference for the associated user.
    };
}
/*
 * SceneManager.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class EngineInstance;
    class IScene;
    
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
        SceneManager(UserID userID, EngineInstance &engineInstance);
        
        ~SceneManager();
        
        ///
        /// Updates the scene currently being presented.
        ///
        void UpdateCurrentScene(UserID userID);
        
        ///
        /// Renders the scene currently being presented.
        ///
        /// @param webSocket Web socket object for the current user.
        ///
        void RenderCurrentScene(UserID userID) const;
        
        ///
        /// Move from the currently presented scene to another one.
        ///
        /// @param sceneName Name of the scene to go to.
        ///
        void GoToScene(UserID userID, std::string_view sceneName);
        
        template<class T>
        const T* GetScene(
            std::string_view sceneName) const {
            
            auto hashCode = Hash(sceneName);
            
            if (GetScenes().contains(hashCode)) {
                
                return static_cast<T*>(GetScenes().at(hashCode).get());
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
        void AddScene(UserID userID, std::string_view sceneName,
                      std::unique_ptr<IScene> scene);
        
        std::map<int, std::unique_ptr<IScene>> &GetScenes() const;
                      
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}
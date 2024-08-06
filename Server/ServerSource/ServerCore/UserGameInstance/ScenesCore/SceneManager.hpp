/*
 * SceneManager.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class UserConnection;
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
        SceneManager(UserConnection &userConnection);
        
        ///
        /// Updates the scene currently being presented.
        ///
        void UpdateCurrentScene();
        
        ///
        /// Renders the scene currently being presented.
        /// 
        /// @param webSocket Web socket object for the current user.
        ///
        void RenderCurrentScene(WebSocket &webSocket) const;
        
        ///
        /// Move from the currently presented scene to another one.
        /// 
        /// @param sceneName Name of the scene to go to.
        ///
        void GoToScene(std::string_view sceneName);
        
      private:
        ///
        /// Add a new scene, used in the ctor.
        /// 
        /// @param sceneName Name of the scene to add.
        /// @param scene The scene object to add.
        ///
        void AddScene(std::string_view sceneName,
                      std::shared_ptr<IScene> scene);
        
        int m_currentScene {0}; ///< Hash code of name of the currently presented scene.
        std::map<int, std::shared_ptr<IScene>> m_scenes; ///< All scenes that has been added in ctor.
        UserConnection &m_userConnection; ///< User connection reference for the associated user.
    };
}
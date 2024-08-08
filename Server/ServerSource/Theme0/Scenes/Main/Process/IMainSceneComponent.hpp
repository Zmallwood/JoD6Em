/*
 * IMainSceneComponent.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class MainScene;
    class UserGameInstanceEngine;
    
    ///
    /// Base class for all components contained in MainScene.
    ///
    class IMainSceneComponent {
        
      public:
        ///
        /// Takes and stores references to key objects for the user.
        ///
        /// @param userConnection User connection associated with user.
        /// @param mainScene Main scene associated with user.
        ///
        IMainSceneComponent(
            const UserGameInstanceEngine& userGameInstanceEngine,
            const MainScene& mainScene);
        
        ///
        /// Optionally overridable for inheriting component classes.
        ///
        virtual void Update() {
        }
        
        ///
        /// Optionally overridable for inheriting component classes.
        /// 
        /// @param webSocket Web socket object associated with user.
        ///
        virtual void Render(WebSocket &webSocket) const {
        }
        
      protected:
        const UserGameInstanceEngine &m_userGameInstanceEngine; ///< User connection object associated with user.
        const MainScene& m_mainScene; ///< Main scene associated with user.
    };
}
/*
 * IMainSceneComponent.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class EngineInstance;
    
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
            const EngineInstance& engineInstance);
        
        ///
        /// Optionally overridable for inheriting component classes.
        ///
        virtual void Update(UserID userID) {
        }
        
        ///
        /// Optionally overridable for inheriting component classes.
        ///
        /// @param webSocket Web socket object associated with user.
        ///
        virtual void Render(UserID userID, WebSocket &webSocket) const {
        }
        
      protected:
        const JoD::EngineInstance& EngineInstance() const {
            
            return m_engineInstance;
        }
        
      private:
        const JoD::EngineInstance &m_engineInstance; ///< User connection object associated with user.
    };
}
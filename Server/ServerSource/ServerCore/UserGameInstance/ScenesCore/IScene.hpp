/*
 * IScene.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/GUICore/GUI.hpp"

namespace JoD {
    
    class EngineInstance;
    
    ///
    /// Pure virtual IScene class of which all scenes inherits.
    ///
    class IScene {
        
      public:
        ///
        /// Construct a new IScene object by forwarding a reference of user connection.
        ///
        /// @param userConnection User connection associated with current user.
        ///
        IScene(JoD::EngineInstance& engineInstance);
        
        ///
        /// Called once for inherited scenes when a new user
        /// has connected and initializes a new set of scenes.
        ///
        virtual void Initialize() {
        }
        
        virtual void OnEnter() {
            
        }
        
        ///
        /// Called each frame in the user engines game loop.
        ///
        void Update(UserID userID);
        
        ///
        /// Called each frame in the user engines game loop.
        ///
        /// @param webSocket Web socket object associated with the user.
        ///
        void Render(UserID userID, WebSocket &webSocket) const;
        
      protected:
        ///
        /// Inheriting scenes specific update operations, called each frame.
        ///
        virtual void UpdateDerived(UserID userID) {}
        
        ///
        /// Inheriting scenes specific render operations, called each frame.
        ///
        /// @param webSocket Web socket object associated with the user.
        ///
        virtual void RenderDerived(
            UserID userID,
            WebSocket
            &webSocket) const {}
        
        JoD::EngineInstance& EngineInstance() const {
            
            return m_engineInstance;
        }
        
        const std::unique_ptr<JoD::GUI>& GUI() const {
            
            return m_gui;
        }
        
      private:
        JoD::EngineInstance &m_engineInstance; ///< User connection object for current user.
        std::unique_ptr<JoD::GUI> m_gui;
    };
}
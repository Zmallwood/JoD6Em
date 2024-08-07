/*
 * IScene.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/GUICore/GUI.hpp"

namespace JoD {
    
    class UserConnection;
    
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
        IScene(UserConnection& userConnection);
        
        ///
        /// Called once for inherited scenes when a new user
        /// has connected and initializes a new set of scenes.
        ///
        virtual void Initialize() {
        }
        
        ///
        /// Called each frame in the user engines game loop.
        ///
        void Update();
        
        ///
        /// Called each frame in the user engines game loop.
        /// 
        /// @param webSocket Web socket object associated with the user.
        ///
        void Render(WebSocket &webSocket) const;
        
      protected:
        ///
        /// Inheriting scenes specific update operations, called each frame.
        ///
        virtual void UpdateDerived() = 0;
        
        ///
        /// Inheriting scenes specific render operations, called each frame.
        /// 
        /// @param webSocket Web socket object associated with the user.
        ///
        virtual void RenderDerived(
            WebSocket
            &webSocket) const = 0;
        
        UserConnection &m_userConnection; ///< User connection object for current user.
        std::unique_ptr<GUI> m_gui;
    };
}
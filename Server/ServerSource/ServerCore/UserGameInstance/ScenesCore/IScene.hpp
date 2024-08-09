/*
 * IScene.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class EngineInstance;
    class GUI;
    
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
        
        ~IScene();
        
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
        
        JoD::EngineInstance& EngineInstance() const;
        
        const std::unique_ptr<JoD::GUI>& GUI() const;
        
      private:
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}
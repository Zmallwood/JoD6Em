/*
 * IScene.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
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
        IScene();
        
        ~IScene();
        
        ///
        /// Called once for inherited scenes when a new user
        /// has connected and initializes a new set of scenes.
        /// 
        /// @param userID User ID for which the scene belongs to.
        ///
        virtual void Initialize(UserID userID) {}
        
        ///
        /// Called when user is navigating to this scene.
        /// 
        /// @param userID User ID for which the scene belongs to.
        ///
        virtual void OnEnter(UserID userID) {}
        
        ///
        /// Called each frame in the user engines game loop.
        /// 
        /// @param userID User ID for which the scene belongs to.
        ///
        void Update(UserID userID);
        
        ///
        /// Called each frame in the user engines game loop.
        /// 
        /// @param userID User ID for which the scene belongs to.
        ///
        void Render(UserID userID) const;
        
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
        virtual void RenderDerived(UserID userID) const {}
        
        ///
        /// Get raw pointer to GUI object of the scene.
        /// 
        /// @return GUI* GUI object raw pointer.
        ///
        GUI* GetGUI() const;
        
      private:
        
        ///
        /// PIMPL idiom to reduce header includes.
        ///
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}

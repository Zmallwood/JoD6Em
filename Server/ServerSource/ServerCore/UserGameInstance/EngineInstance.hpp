/*
 * EngineInstance.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class MouseInput;
    class Player;
    class SceneManager;
    class TextMessages;
    
    ///
    /// An instance of this engine is created for every connected user.
    ///
    class EngineInstance {
        
      public:
        ///
        /// Stores an user connection reference and initializes members.
        ///
        EngineInstance();
        
        ~EngineInstance();
        
        ///
        /// Updates everything that needs it in the game loop.
        ///
        void Update(UserID userID);
        
        ///
        /// Renders everything that needs it in the game loop.
        /// 
        /// @param webSocket Web socket object associated with the users connection.
        ///
        void Render(UserID userID, WebSocket &webSocket) const;
        
        ///
        /// Get the Aspect Ratio for the web browser canvas of the user.
        /// 
        /// @return float Users aspect ratio.
        ///
        float GetAspectRatio() const;
        
        PointF MousePosition() const;
        
        void SetMousePosition(PointF value);
        
        void SetCanvasSize(Size value);
        
        JoD::MouseInput* MouseInput() const;
        
        JoD::SceneManager *SceneManager() const;
        
        JoD::Player *Player() const;
        
        JoD::TextMessages *TextOut() const;
        
      private:
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}
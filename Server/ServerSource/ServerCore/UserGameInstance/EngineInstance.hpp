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
    class Cursor;
    
    ///
    /// An instance of this engine is created for every connected user.
    ///
    class EngineInstance {
        
      public:
        
        ///
        /// Construct a new EngineInstance object for an user.
        ///
        /// @param userID User ID for the user which the EngineInstance is created.
        /// @param socket Socket object associated with the user.
        ///
        EngineInstance(UserID userID, Socket socket);
        
        ///
        /// Destroy the EngineInstance object, necessary for PIMPL idiom.
        ///
        ///
        ~EngineInstance();
        
        ///
        /// Reset certain states at the beginning of each frame.
        ///
        void Reset();
        
        ///
        /// Updates everything that needs it in the game loop.
        ///
        /// @param userID User ID for the user which engine instance is to updated.
        ///
        void Update(UserID userID);
        
        ///
        /// Renders everything that needs it in the game loop.
        ///
        /// @param userID User ID for the user which engine instance is to rendered.
        ///
        void Render(UserID userID) const;
        
        ///
        /// Get the Aspect Ratio for the web browser canvas of the user.
        ///
        /// @return float Users aspect ratio.
        ///
        float GetAspectRatio() const;
        
        ///
        /// Get the mouse position for the user.
        /// 
        /// @return PointF Current mouse position value.
        ///
        PointF GetMousePosition() const;
        
        ///
        /// Set the mouse position for the user.
        /// 
        /// @param value New mouse position value.
        ///
        void SetMousePosition(PointF value);
        
        ///
        /// Set the canvas size for the user.
        /// 
        /// @param value New canvas size value.
        ///
        void SetCanvasSize(Size value);
        
        ///
        /// Get the MouseInput object for the user.
        /// 
        /// @return MouseInput* Users MouseInput object.
        ///
        MouseInput* GetMouseInput() const;
        
        ///
        /// Get the SceneManager object for the user.
        /// 
        /// @return SceneManager* Users SceneManager object.
        ///
        SceneManager *GetSceneManager() const;
        
        ///
        /// Get the Player object for the user.
        /// 
        /// @return Player* Users Player object.
        ///
        Player *GetPlayer() const;
        
        ///
        /// Get the TextMessages object for the user.
        /// 
        /// @return TextMessages* Users TextMessages object.
        ///
        TextMessages *GetTextMessages() const;
        
        ///
        /// Get the WebSocket object for the user.
        /// 
        /// @return WebSocket* Users WebSocket object.
        ///
        WebSocket *GetWebSocket() const;
        
        ///
        /// Get the Cursor object for the user.
        /// 
        /// @return Cursor* Users Cursor object.
        ///
        Cursor *GetCursor() const;
        
      private:
        
        ///
        /// PIMPL idiom, used to reduce number of includes
        /// in this header.
        ///
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl; ///< PIMPL idiom object.
    };
}

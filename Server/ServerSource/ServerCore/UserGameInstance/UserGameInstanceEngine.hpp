/*
 * UserGameInstanceEngine.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */


#pragma once

namespace JoD {
    
    class MouseInput;
    class SceneManager;
    class ServerFPSCounter;
    class Player;
    class Cursor;
    
    ///
    /// An instance of this engine is created for every connected user.
    ///
    class UserGameInstanceEngine {
        
      public:
        ///
        /// Stores an user connection reference and initializes members.
        ///
        UserGameInstanceEngine();
        
        ///
        /// Updates everything that needs it in the game loop.
        ///
        void Update();
        
        ///
        /// Renders everything that needs it in the game loop.
        /// 
        /// @param webSocket Web socket object associated with the users connection.
        ///
        void Render(WebSocket &webSocket) const;
        
        ///
        /// Get the Aspect Ratio for the web browser canvas of the user.
        /// 
        /// @return float Users aspect ratio.
        ///
        float GetAspectRatio() const;
        
        PointF m_mousePosition; ///< Current mosue position in the browser canvas.
        Size m_canvasSize; ///< Size of canvas in browser.
        std::shared_ptr<MouseInput> m_mouseInput; ///< Handles mouse input and provides state.
        std::shared_ptr<SceneManager> m_sceneManager; ///< Manages game scenes for the user s instance.
        std::shared_ptr<Player> m_player; ///< Player instance for the user.
        std::shared_ptr<Cursor> m_cursor; ///< Custom cursor which replaces default system cursor.
        
      private:
        std::shared_ptr<ServerFPSCounter> m_serverFPSCounter; ///< Server side FPS counter.
    };
}
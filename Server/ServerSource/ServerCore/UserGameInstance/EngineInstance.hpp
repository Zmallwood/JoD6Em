/*
 * EngineInstance.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerFPSCounter.hpp"
#include "ScenesCore/SceneManager.hpp"
#include "ServerCore/UserGameInstance/Cursor/Cursor.hpp"
#include <memory>

namespace JoD {
    
    ///
    /// An instance of this engine is created for every connected user.
    ///
    class EngineInstance {
        
      public:
        ///
        /// Stores an user connection reference and initializes members.
        ///
        EngineInstance();
        
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
        
        PointF MousePosition() const {
            
            return m_mousePosition;
        }
        
        void SetMousePosition(PointF value) {
            
            m_mousePosition = value;
        }
        
        void SetCanvasSize(Size value) {
            
            m_canvasSize = value;
        }
        
        const std::unique_ptr<JoD::MouseInput> &MouseInput() const {
            
            return m_mouseInput;
        }
        
        const std::unique_ptr<JoD::SceneManager> &SceneManager() const {
            
            return m_sceneManager;
        }
        
        const std::unique_ptr<JoD::Player> &Player() const {
            
            return m_player;
        }
        
      private:
        PointF m_mousePosition; ///< Current mosue position in the browser canvas.
        Size m_canvasSize; ///< Size of canvas in browser.
        std::unique_ptr<JoD::MouseInput> m_mouseInput; ///< Handles mouse input and provides state.
        std::unique_ptr<JoD::SceneManager> m_sceneManager; ///< Manages game scenes for the user s instance.
        std::unique_ptr<JoD::Player> m_player; ///< Player instance for the user.
        std::unique_ptr<Cursor> m_cursor; ///< Custom cursor which replaces default system cursor.
        std::unique_ptr<ServerFPSCounter> m_serverFPSCounter; ///< Server side FPS counter.
    };
}
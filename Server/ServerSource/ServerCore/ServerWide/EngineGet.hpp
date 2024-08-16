/*
 * EngineInstancesManager.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class EngineInstance;
    class Player;
    class SceneManager;
    class MouseInput;
    class TextMessages;
    class Cursor;
    
    ///
    /// Provides access to all components associated with the engine instances
    /// of all connected users.
    ///
    class EngineGet {
        
      public:
        ///
        /// Creates PIMPL object.
        ///
        EngineGet();
        
        ///
        /// Required for using PIMPL idiom.
        ///
        ~EngineGet();
        
        ///
        /// Create a new engine instance for a new user just connected.
        ///
        /// @param socket Socket object associated with the user.
        /// @return UserID Unique user ID associated with the user
        ///                and which is used to access engine components.
        ///
        UserID CreateNewEngineInstance(Socket socket);
        
        ///
        /// Get the Engine Instance object associated with a certain user.
        ///
        /// @param userID User ID for which the EngineInstance should be retrieved.
        /// @return EngineInstance* The EngineInstance that belongs to the user.
        ///
        EngineInstance* GetEngineInstance(UserID userID) const;
        
        ///
        /// Get the mouse position that belongs to a certain user.
        ///
        /// @param userID User ID for the user which mouse postion should be retrieved.
        /// @return std::optional<PointF> Mouse position or nullopt if none exists.
        ///
        std::optional<PointF> GetMousePosition(UserID userID) const;
        
        ///
        /// Get the aspect ratio that belongs to a certain user.
        ///
        /// @param userID User ID for the user which aspect ratio should be retrieved.
        /// @return std::optional<float> Aspect ratio or nullopt if none exists.
        ///
        std::optional<float> GetAspectRatio(UserID userID) const;
        
        ///
        /// Get the Player object that belongs to a certain user.
        ///
        /// @param userID User ID for the user which player object should be retrieved.
        /// @return Player* Player object or nullptr if none exists.
        ///
        Player* GetPlayer(UserID userID) const;
        
        ///
        /// Get the Scene Manager object that belongs to a certain user.
        ///
        /// @param userID User ID for the user which SceneManager object should be retrieved.
        /// @return SceneManager* SceneManager object or nullptr if none exists.
        ///
        SceneManager* GetSceneManager(UserID userID) const;
        
        ///
        /// Get the Mouse Input object that belongs to a certain user.
        ///
        /// @param userID User ID for the user which MouseInput object should be retrieved.
        /// @return MouseInput* MouseInput object or nullptr if none exists.
        ///
        MouseInput* GetMouseInput(UserID userID) const;
        
        ///
        /// Get the Text Messages object that belongs to a certain user.
        ///
        /// @param userID User ID for the user which TextMessages object should be retrieved.
        /// @return TextMessages* TextMessages object or nullptr if none exists.
        ///
        TextMessages* GetTextMessages(UserID userID) const;
        
        ///
        /// Get the Web Socket object that belongs to a certain user.
        ///
        /// @param userID User ID for the user which WebSocket object should be retrieved.
        /// @return WebSocket* WebSocket object or nullptr if none exists.
        ///
        WebSocket *GetWebSocket(UserID userID) const;
        
        Cursor *GetCursor(UserID userID) const;
        
      private:
        ///
        /// PIMPL idiom to reduce header includes.
        ///
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl; ///< PIMPL idiom to reduce header includes.
    };
}
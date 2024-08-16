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
        /// Stores an user connection reference and initializes members.
        ///
        EngineInstance(UserID userID, Socket socket);

        ~EngineInstance();
        
        void Reset();

        ///
        /// Updates everything that needs it in the game loop.
        ///
        void Update(UserID userID);

        ///
        /// Renders everything that needs it in the game loop.
        ///
        /// @param webSocket Web socket object associated with the users connection.
        ///
        void Render(UserID userID) const;

        ///
        /// Get the Aspect Ratio for the web browser canvas of the user.
        ///
        /// @return float Users aspect ratio.
        ///
        float GetAspectRatio() const;

        PointF GetMousePosition() const;

        void SetMousePosition(PointF value);

        void SetCanvasSize(Size value);

        JoD::MouseInput* GetMouseInput() const;

        JoD::SceneManager *GetSceneManager() const;

        JoD::Player *GetPlayer() const;

        JoD::TextMessages *GetTextMessages() const;

        WebSocket *GetWebSocket() const;
        
        Cursor *GetCursor() const;

      private:

        struct Impl;

        std::unique_ptr<Impl> m_pImpl;
    };
}

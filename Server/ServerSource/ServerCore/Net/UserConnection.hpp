/*
 * UserConnection.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Created for each user that connects to the web socket server.
    ///
    class UserConnection {
        
      public:
        ///
        /// Starts a web socket loop thread for the user.
        ///
        /// @param socket Socket object obtained from web
        ///               socket server and associated with the user.
        ///
        UserConnection(Socket socket);
        
        ~UserConnection();
        
      private:
        ///
        /// Running game loop for user.
        ///
        /// @param socket Socket object.
        ///
        void DoSession(UserID userID);
        
        ///
        /// Running loop for reading incoming web socket messages and handle them.
        ///
        /// @param webSocket Socket object.
        ///
        void DoSessionNested(WebSocket* webSocket);
        
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}
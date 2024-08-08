/*
 * UserConnection.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/EngineInstance.hpp"

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
        
      private:
        ///
        /// Running game loop for user.
        ///
        /// @param socket Socket object.
        ///
        void DoSession(Socket socket);
        
        ///
        /// Running loop for reading incoming web socket messages and handle them.
        /// 
        /// @param webSocket Socket object.
        ///
        void DoSessionNested(WebSocket* webSocket);
        
        std::unique_ptr<EngineInstance>
        m_engineInstance; ///< Engine running for this specific user.
    };
}
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
    
    ///
    /// Destroy the User Connection object. Needed by PIMPL idiom.
    ///
    ~UserConnection();
    
  private:
    ///
    /// Running game loop for user.
    ///
    /// @param userID ID of user for which to running the game loop.
    ///
    void RunUserGameLoop(UserID userID);
    
    ///
    /// Running loop for reading incoming web socket messages and handle them.
    ///
    /// @param webSocket Websocket object.
    ///
    void HandleIncoming(WebSocket* webSocket);
    
    ///
    /// PIMPL struct defined in source file.
    ///
    struct Impl;
    
    std::unique_ptr<Impl> m_pImpl;     ///< PIMPL idiom used for compilation speed reasons.
};

}
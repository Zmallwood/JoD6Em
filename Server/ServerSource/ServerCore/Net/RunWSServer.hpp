/*
 * RunWebSocketServer.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
///  Run web socket server.
///
/// @param socketAddress Address to the machine to run the web socket server.
/// @param socketPort Port to run the web socket server on.
///
void RunWSServer(
    std::string_view socketAddress,
    std::string_view socketPort);
    
}
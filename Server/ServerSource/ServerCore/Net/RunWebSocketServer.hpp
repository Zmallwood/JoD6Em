/*
 * RunWebSocketServer.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    void RunWebSocketServer(
        std::string_view socketAddress,
        std::string_view socketPort);
}
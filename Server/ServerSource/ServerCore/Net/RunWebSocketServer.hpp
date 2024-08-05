/*
 * RunWebSocketServer.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    void RunWebSocketServer(
        std::string socketAddress,
        std::string socketPort);
}
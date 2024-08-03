/*
 * RunWebSocketServer.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    void RunWebSocketServer(std::string socket_address,
                            std::string socket_port);
}
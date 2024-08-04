/*
 * RunWebSocketServer.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RunWebSocketServer.hpp"
#include "WebSocketServer.hpp"

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

namespace JoD {
    void RunWebSocketServer(std::string socket_address,
                            std::string socket_port) {
        _<WebSocketServer>().Run(socket_address, socket_port);
    }
}
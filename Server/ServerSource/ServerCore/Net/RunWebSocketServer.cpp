/*
 * RunWebSocketServer.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RunWebSocketServer.h"
#include "WebSocketServer.h"

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

namespace jod {
    void RunWebSocketServer(std::string socket_address,
                            std::string socket_port) {
        _<web_socket_server>().run(socket_address, socket_port);
    }
}
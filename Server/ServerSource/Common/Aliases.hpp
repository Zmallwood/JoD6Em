/*
 * Aliases.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
using Socket = boost::asio::ip::tcp::socket;               ///< Socket object.
using WebSocket = boost::beast::websocket::stream<Socket>; ///< Web socket object.
}
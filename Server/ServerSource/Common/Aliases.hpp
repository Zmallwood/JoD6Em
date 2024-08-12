/*
 * Aliases.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    using UserID = unsigned long long;
    
    using Socket = boost::asio::ip::tcp::socket;
    
    using WebSocket = ///< Web socket object.
                      boost::beast::websocket::stream<boost::asio::ip::tcp::socket>;
}
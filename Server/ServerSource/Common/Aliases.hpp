/*
 * Aliases.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    using UserID = unsigned long long; ///< Unique identifier for a connected user.
    
    using Socket = boost::asio::ip::tcp::socket; ///< Socket object.
    
    using WebSocket = ///< Web socket object.
                      boost::beast::websocket::stream<Socket>;
}
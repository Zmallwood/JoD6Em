/*
 * Aliases.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    using WebSocket = boost::beast::websocket::stream<boost::asio::ip::
                                                      tcp::socket>;
}
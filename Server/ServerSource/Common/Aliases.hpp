/*
 * Aliases.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    using WebSocket = boost::beast::websocket::stream<boost::asio::ip::
                                                      tcp::socket>;

    using TimePoint = std::chrono::high_resolution_clock::time_point;

    using Duration = std::chrono::high_resolution_clock::duration;

    using Millis = std::chrono::milliseconds;

    static auto Now = std::chrono::high_resolution_clock::now;
}
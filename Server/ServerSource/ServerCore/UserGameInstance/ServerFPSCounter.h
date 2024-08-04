/*
 * FPSCounter.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class user_connection;

    class server_fps_counter {
    public:
        server_fps_counter(user_connection& user_connection);

        void update();
        
        void render(boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& ws);
        
    private:
        int m_fps = 0;
        int m_frames_count = 0;
        std::chrono::high_resolution_clock::time_point m_ticks_last_update = std::chrono::high_resolution_clock::now();
        user_connection& m_user_connection;
    };
}
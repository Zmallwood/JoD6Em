/*
 * fps_counter.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "fps_counter.h"
#include "ServerCore/Net/user_connection.h"

namespace jod {
    fps_counter::fps_counter(user_connection& user_connection)
        : m_user_connection(user_connection) {
    }
    
    void fps_counter::update() {
        if (std::chrono::high_resolution_clock::now() >
            m_ticks_last_update + std::chrono::high_resolution_clock::duration(
                std::chrono::milliseconds(1000))) {
            m_fps = m_frames_count;
            m_frames_count = 0;
            m_ticks_last_update = std::chrono::high_resolution_clock::now();
        }
        m_frames_count++;
    }
    
    void fps_counter::render(boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& ws) {
        m_user_connection.send_text_draw_instruction(ws, "Server fps: " + std::to_string(m_fps), {0.9f, 0.1f});
    }
}
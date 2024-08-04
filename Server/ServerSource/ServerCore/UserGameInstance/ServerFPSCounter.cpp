/*
 * FPSCounter.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ServerFPSCounter.hpp"
#include "ServerCore/Net/UserConnection.hpp"

namespace JoD {
    ServerFPSCounter::ServerFPSCounter(UserConnection& user_connection)
        : m_user_connection(user_connection) {
    }
    
    void ServerFPSCounter::Update() {
        if (Now() > m_ticks_last_update + Duration(Millis(1000))) {
            m_fps = m_frames_count;
            m_frames_count = 0;
            m_ticks_last_update = Now();
        }
        m_frames_count++;
    }
    
    void ServerFPSCounter::Render(WebSocket& ws) {
        m_user_connection.SendTextDrawInstruction(
            ws,
            "Server fps: " + std::to_string(m_fps), {0.9f, 0.1f});
    }
}
/*
 * FPSCounter.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ServerFPSCounter.hpp"
#include "ServerCore/Net/UserConnection.hpp"

namespace JoD {
    
    ServerFPSCounter::ServerFPSCounter(UserConnection& userConnection)
        : m_userConnection(userConnection) {
        
    }
    
    void ServerFPSCounter::Update() {
        
        if (Now() > m_ticksLastUpdate + Duration(Millis(1000))) {
            m_fps = m_framesCount;
            m_framesCount = 0;
            m_ticksLastUpdate = Now();
        }
        m_framesCount++;
    }
    
    void ServerFPSCounter::Render(WebSocket& ws) const {
        
        m_userConnection.SendTextDrawInstruction(
            ws,
            "Server fps: " + std::to_string(m_fps), {0.8f, 0.1f});
    }
}
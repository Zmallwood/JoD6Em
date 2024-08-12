/*
 * FPSCounter.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ServerFPSCounter.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
    
    void ServerFPSCounter::Update() {
        
        if (Now() > m_ticksLastUpdate + Duration(Millis(1000))) {
            
            m_fps = m_framesCount;
            
            m_framesCount = 0;
            
            m_ticksLastUpdate = Now();
        }
        
        m_framesCount++;
    }
    
    void ServerFPSCounter::Render(UserID userID) const {
        
        SendTextDrawInstruction(
            userID,
            "Server fps: " + std::to_string(m_fps), {0.8f, 0.1f});
    }
}
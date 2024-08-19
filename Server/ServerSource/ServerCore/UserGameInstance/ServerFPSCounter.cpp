/*
 * ServerFPSCounter.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ServerFPSCounter.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {

void ServerFPSCounter::Update() {
    
// Recalculate FPS every second.
    if (Now() > m_timeLastUpdate + Duration(Millis(1000))) {
        
// FPS = number of frames counted during one second.
        m_fps = m_framesCount;
        
// Reset number of frames counted.
        m_framesCount = 0;
        
// Remember which point in time we calculated this FPS value.
        m_timeLastUpdate = Now();
    }
    
// Add to frames counter every frame.
    m_framesCount++;
}

void ServerFPSCounter::Render(UserID userID) const {
    
// Draw the FPS text to the canvas.
    UserSendDrawText(
        userID,
        "Server fps: " + std::to_string(m_fps), k_position);
}

}
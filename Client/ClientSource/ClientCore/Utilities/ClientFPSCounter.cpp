/*
 * FPSCounter.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ClientFPSCounter.hpp"
#include "ClientCore/Graphics/Rendering/Text/TextRenderer.hpp"

namespace JoD {
    
    ClientFPSCounter::ClientFPSCounter() {
        
        // Allocate resource ID for drawing the FPS text.
        m_rid = _<TextRenderer>().NewString();
    }
    
    void ClientFPSCounter::Update() {
        
        // Update every second.
        if (Now() > m_timeLastUpdate + Duration(Millis(1000))) {
            
            // Obtain the current FPS.
            m_fps = m_framesCount;
            
            // Reset frames counting.
            m_framesCount = 0;
            
            // Remember this as last time FPS was updated.
            m_timeLastUpdate = Now();
        }
        
        // Count number of frames.
        m_framesCount++;
    }
    
    void ClientFPSCounter::Render() const {
        
        // Draw FPS text to canvas.
        _<TextRenderer>().DrawString(
            m_rid, "Client fps: " + std::to_string(m_fps),
            {0.8f, 0.05f});
    }
}
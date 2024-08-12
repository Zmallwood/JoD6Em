/*
 * FPSCounter.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ClientFPSCounter.hpp"
#include "ClientCore/Graphics/Rendering/Text/TextRenderer.hpp"

namespace JoD {
    
    ClientFPSCounter::ClientFPSCounter() {
        
        m_rid = _<TextRenderer>().NewString();
    }
    
    void ClientFPSCounter::Update() {
        
        if (Now() > m_ticksLastUpdate + Duration(Millis(1000))) {
            
            m_fps = m_framesCount;
            
            m_framesCount = 0;
            
            m_ticksLastUpdate = Now();
        }
        
        m_framesCount++;  
    }
    
    void ClientFPSCounter::Render() const {
        
        _<TextRenderer>().DrawString(
            m_rid, "Client fps: " + std::to_string(m_fps),
            {0.8f, 0.05f});
    }
}
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
    
    void ClientFPSCounter::Update()      {
        if (GetTicks() > m_ticks_last_update + 1000) {
            m_fps = m_frames_count;
            m_frames_count = 0;
            m_ticks_last_update = GetTicks();
        }
        m_frames_count++;
    }
    
    void ClientFPSCounter::Render()      {
        _<TextRenderer>().DrawString(
            m_rid, "Client fps: " + std::to_string(m_fps),
            {0.9f, 0.05f});
    }
}
/*
 * FPSCounter.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ClientFPSCounter.h"
#include "ClientCore/Graphics/Rendering/Text/TextRenderer.h"

namespace jod {
    client_fps_counter::client_fps_counter() {
        m_rid = _<text_renderer>().new_string();
    }
    
    void client_fps_counter::update()      {
        if (get_ticks() > m_ticks_last_update + 1000) {
            m_fps = m_frames_count;
            m_frames_count = 0;
            m_ticks_last_update = get_ticks();
        }
        m_frames_count++;
    }
    
    void client_fps_counter::render()      {
        _<text_renderer>().draw_string(
            m_rid, "Client fps: " + std::to_string(m_fps),
            {0.9f, 0.05f});
    }
}
/*
 * fps_counter.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class fps_counter {
    public:
        fps_counter();
        
        void update();
        
        void render();
        
    private:
        rid m_rid;
        int m_frames_count = 0;
        int m_fps = 0;
        int m_ticks_last_update = 0;
    };
}
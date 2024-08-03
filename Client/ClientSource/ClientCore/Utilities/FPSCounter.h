/*
 * FPSCounter.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    //! \brief Client side FPS counter rendered to the canvas.
    class fps_counter {
    public:
        //! \brief Construct a new fps counter object by allocated rendering resources.
        fps_counter();
        
        //! \brief Compute the current FPS.
        void update();
        
        //! \brief Render the computed FPS to the canvas.
        void render();
        
    private:
        rid m_rid;
        int m_frames_count = 0;
        int m_fps = 0;
        int m_ticks_last_update = 0;
    };
}
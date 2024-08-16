/*
 * FPSCounter.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Client side FPS counter rendered to the canvas.
    ///
    class ClientFPSCounter {
        
      public:
        ///
        /// Construct a new fps counter object by allocated rendering resources.
        ///
        ClientFPSCounter();
        
        ///
        /// Compute the current FPS.
        ///
        void Update();
        
        ///
        /// Render the computed FPS to the canvas.
        ///
        void Render() const;
        
      private:
        RID m_rid {0};                       ///< RID used to render the FPS text.
        int m_framesCount {0};               ///< Number of frames counted since last FPS update.
        int m_fps {0};                       ///< Last calculated FPS value.
        TimePoint m_ticksLastUpdate {Now()}; ///< Last time the FPS was calculated.
    };
}
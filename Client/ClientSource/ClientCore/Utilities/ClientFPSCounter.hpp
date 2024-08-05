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
        RID m_rid;
        
        int m_framesCount {0};
        
        int m_fps {0};
        
        int m_ticksLastUpdate {0};
    };
}
/*
 * FPSCounter.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Server side FPS counter for a single user.
    ///
    class ServerFPSCounter {
        
      public:

        ///
        /// Update the object by producing the final FPS value.
        ///
        void Update();
        
        ///
        /// Render the FPS value as string to canvas.
        /// 
        /// @param webSocket Web socket object for the current user.
        ///
        void Render(WebSocket& webSocket) const;
        
      private:
        int m_fps {0}; ///< Last calculated FPS value.
        int m_framesCount {0}; ///< Counting of nummer of frames reached in one second.
        TimePoint m_ticksLastUpdate {Now()}; ///< Last time the FPS was calculated.
    };
}
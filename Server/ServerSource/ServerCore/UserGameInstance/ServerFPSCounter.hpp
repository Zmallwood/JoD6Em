/*
 * ServerFPSCounter.hpp
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
        /// @param userID User ID for which this ServerFPSCounter belongs to.
        ///
        void Render(UserID userID) const;

      private:

        // Members

        int m_fps {0}; ///< Last calculated FPS value.

        int m_framesCount {0}; ///< Counting of nummer of frames reached in one second.

        TimePoint m_timeLastUpdate {Now()}; ///< Last time the FPS was calculated.
        
        const PointF k_position {0.8f, 0.1f}; ///< Position in canvas where FPS text is drawn.
    };
}

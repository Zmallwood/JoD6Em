/*
 * FPSCounter.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class UserConnection;
    
    ///
    /// Server side FPS counter for a single user.
    ///
    class ServerFPSCounter {
        
      public:
        ///
        /// Construct a new instance by forwarding a user
        /// connection reference for the current user.
        ///
        /// @param userConnection User connection reference for the current user.
        ///
        ServerFPSCounter(UserConnection& userConnection);
        
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
        UserConnection& m_userConnection; ///< Reference to user connection for associated user.
    };
}
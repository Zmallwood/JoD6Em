/*
 * ClientEngine.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Engine for the client.
    ///
    class ClientEngine {
        
      public:
        ///
        /// Run the client engine.
        ///
        void Run() const;
        
        ///
        /// Poll input events from user.
        ///
        void PollEvents();
        
        bool m_running = true; ///< Engine is running as long as this is set to true.
    };
}
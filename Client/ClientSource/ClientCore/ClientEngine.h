/*
 * ClientEngine.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    //! \brief Engine for the client.
    class client_engine {
    public:
        //! \brief Run the client engine.
        void run() const;
        
        //! \brief Poll input events from user.
        void poll_events();
        
        bool m_running = true; //!< Engine is running as long as this is set to true.
    };
}
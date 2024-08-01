// mouse_movement.h
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
///////////////////////////////////////////////////////////

#pragma once

namespace jod {
    class client;

    class mouse_movement {
    public:
        mouse_movement(client &client);
        
        void update();
        
    private:
        client &m_client;
    };
}
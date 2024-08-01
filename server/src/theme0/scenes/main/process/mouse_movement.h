// mouse_movement.h
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
///////////////////////////////////////////////////////////

#pragma once

namespace jod {
    class user_connection;

    class mouse_movement {
    public:
        mouse_movement(user_connection &user_connection);
        
        void update();
        
    private:
        user_connection &m_user_connection;
    };
}
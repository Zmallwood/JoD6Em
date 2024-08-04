/*
 * MouseMovement.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class UserConnection;

    class MouseMovement {
    public:
        MouseMovement(UserConnection &user_connection);
        
        void Update();
        
    private:
        UserConnection &m_user_connection;
    };
}
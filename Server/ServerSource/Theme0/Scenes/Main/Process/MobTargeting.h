/*
 * MobTargeting.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class UserConnection;
    class Mob;

    class MobTargeting {
    public:
        MobTargeting(UserConnection& user_connection);

        void Update();

        std::shared_ptr<Mob> m_targeted_creature;
        
    private:
        UserConnection &m_user_connection;
    };
}
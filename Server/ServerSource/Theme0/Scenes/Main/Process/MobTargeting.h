/*
 * MobTargeting.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class user_connection;
    class mob;

    class mob_targeting {
    public:
        mob_targeting(user_connection& user_connection);

        void update();

        std::shared_ptr<mob> m_targeted_creature;
        
    private:
        user_connection &m_user_connection;
    };
}
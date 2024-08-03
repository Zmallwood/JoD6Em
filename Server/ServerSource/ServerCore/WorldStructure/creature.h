/*
 * creature.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class creature {
    public:
        creature(std::string_view mob_name, int level);

        int m_level;
        int m_type = 0;
        int m_patk = 0;
        int m_matk = 0;
        int m_pdef = 0;
        int m_mdef = 0;
        float m_atk_speed = 0;
        int m_hp = 0;
        int m_exp = 0;
    };
}
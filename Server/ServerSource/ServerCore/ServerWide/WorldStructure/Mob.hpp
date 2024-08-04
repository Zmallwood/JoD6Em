/*
 * Creature.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class Mob {
    public:
        Mob(std::string_view mobName, int level);

        int m_level = 0;
        int m_type = 0;
        int m_pAtk = 0;
        int m_mAtk = 0;
        int m_pDef = 0;
        int m_mDef = 0;
        float m_atkSpeed = 0;
        int m_hp = 0;
        int m_exp = 0;
    };
}
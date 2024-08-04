/*
 * Creature.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Mob.h"

namespace JoD {
    Mob::Mob(std::string_view mob_name,
                       int level) : m_type(Hash(mob_name)) {
        m_level = level;
        m_patk = level;
        m_matk = 0;
        m_pdef = level;
        m_mdef = level;
        m_atk_speed = level/1.0f;
        m_hp = level*5;
        m_exp = level*5;
    }
}
/*
 * Creature.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Creature.hpp"

namespace JoD {
    
    Creature::Creature(std::string_view creatureName,
             int level) : m_type(Hash(creatureName)) {
        
        m_level = level;
        m_pAtk = level;
        m_mAtk = 0;
        m_pDef = level;
        m_mDef = level;
        m_atkSpeed = level/1.0f;
        m_hp = level*5;
        m_exp = level*5;
        
        m_hunger = static_cast<float>(rand()) / RAND_MAX;
    }
    
    void Creature::Hit(int damage) {
        
        if (IsDead()) {
            
            return;
        }
        
        m_hp -= damage;
        m_ticksLastHitFromOther = Now();
    }
    
    bool Creature::IsDead() const {
        
        return m_hp <= 0;
    }
    
    void Creature::InflictDeath() {
        
        m_hp = 0;
    }
}
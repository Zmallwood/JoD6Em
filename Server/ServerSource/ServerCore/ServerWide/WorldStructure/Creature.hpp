/*
 * Creature.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "CreatureMaturity.hpp"

namespace JoD {
    
    ///
    /// Combatable creature object which can be positioned on a tile.
    ///
    class Creature {
        
      public:
        ///
        /// Construct a new Creature object.
        ///
        /// @param creatureName Creature type name.
        /// @param level Initial level, determines all the stats of the creature.
        ///
        Creature(std::string_view creatureName, int level);
        
        void Hit(int damage);
        
        int GetType() const {
            
            return m_type;
        }
        
        int GetLevel() const {
            
            return m_level;
        }
        
        int GetHP() const {
            
            return m_hp;
        }
        
        int GetExp() const {
            
            return m_exp;
        }
        
        TimePoint GetTicksLastHitFromOther() const {
            
            return m_ticksLastHitFromOther;
        }
        
        bool IsDead() const;
        
        void InflictDeath();
        
        float m_hunger {0.0f};
        
      private:
        int m_type {0}; ///< Hash code of creature type name.
        int m_level {0}; ///< Level, as provided in ctor.
        int m_pAtk {0}; ///< Physical attack.
        int m_mAtk {0}; ///< Magic attack.
        int m_pDef {0}; ///< Physical defense.
        int m_mDef {0}; ///< Magic defense.
        float m_atkSpeed {0}; ///< Attack speed.
        int m_hp {0}; ///< Health points.
        int m_exp {0}; ///< Experience gained when defeating this creature.
        TimePoint m_ticksLastHitFromOther {Now()};
        CreatureMaturity m_maturity {CreatureMaturity::Mature};
    };
}
/*
 * Creature.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Combatable mob object which can be positioned on a tile.
    ///
    class Mob {
        
      public:
        ///
        /// Construct a new Mob object.
        ///
        /// @param mobName Mob type name.
        /// @param level Initial level, determines all the stats of the mob.
        ///
        Mob(std::string_view mobName, int level);
        
        void Hit(int damage);
        
        int GetType() const {
            
            return m_type;
        }
        
        int GetLevel() const {
            
            return m_level;
        }
        
        TimePoint GetTicksLastHitFromOther() const {
            
            return m_ticksLastHitFromOther;
        }
        
      private:
        int m_type {0}; ///< Hash code of mob type name.
        int m_level {0}; ///< Level, as provided in ctor.
        int m_pAtk {0}; ///< Physical attack.
        int m_mAtk {0}; ///< Magic attack.
        int m_pDef {0}; ///< Physical defense.
        int m_mDef {0}; ///< Magic defense.
        float m_atkSpeed {0}; ///< Attack speed.
        int m_hp {0}; ///< Health points.
        int m_exp {0}; ///< Experience gained when defeating this mob.
        TimePoint m_ticksLastHitFromOther {Now()};
    };
}
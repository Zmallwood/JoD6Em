/*
 * Tile.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "Object.hpp"

namespace JoD {
    
    class Mob;
    
    ///
    /// Represents a square tile in the game world.
    ///
    class Tile {
        
      public:
        int GetGround() const {
            
            return m_ground;
        }
        
        void SetGround(int value) {
            
            m_ground = value;
        }
        
        const std::unique_ptr<Object> &GetObject() const {
            
            return m_object;
        }
        
        void SetObject(std::unique_ptr<Object> value) {
            
            m_object = std::move(value);
        }
        
        const std::shared_ptr<Mob> GetMob() const {
            
            return m_mob;
        }
        
        void SetMob(std::shared_ptr<Mob> value) {
            
            m_mob = value;
        }
        
      private:
        int m_ground {0}; ///< Hash code for ground type.
        std::unique_ptr<Object> m_object; ///< Hash code for object type name, nullptr means no object.
        std::shared_ptr<Mob> m_mob; ///< Mob currently occupying this tile, nullptr means no mob.
    };
}
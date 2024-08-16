/*
 * Player.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Core player objects, of which one is created for each connecting user.
    ///
    class Player {
        
      public:
        void TryMoveNorth(UserID userID);
        
        void TryMoveEast(UserID userID);
        
        void TryMoveSouth(UserID userID);
        
        void TryMoveWest(UserID userID);
        
        void TryMoveNorthEast(UserID userID);
        
        void TryMoveSouthEast(UserID userID);
        
        void TryMoveSouthWest(UserID userID);
        
        void TryMoveNorthWest(UserID userID);
        
        void Hit(int damage);
        
        std::string GetName() const {
            
            return m_name;
        }
        
        Point GetCoord() const {
            
            return m_coord;
        }
        
        std::optional<Point> GetDestCoord() const {
            
            return m_destCoord;
        }
        
        void SetDestCoord(std::optional<Point> value) {
            
            m_destCoord = value;
        }
        
        TimePoint GetTicksLastMove() const {
            
            return m_ticksLastMove;
        }
        
        void SetTicksLastMove(TimePoint value) {
            
            m_ticksLastMove = value;
        }
        
        float GetMovementSpeed() const {
            
            return m_movementSpeed;
        }
        
        float GetExperience() const {
            
            return m_experience;
        }
        
        void AddExperience(int value) {
            
            m_experience += value;
        }
        
        TimePoint GetTicksLastAttackOnOther() const {
            
            return m_ticksLastAttackOnOther;
        }
        
        void SetTicksLastAttackOnOther(TimePoint value) {
            
            m_ticksLastAttackOnOther = value;
        }
        
        float GetAttackSpeed() const {
            
            return m_attackSpeed;
        }
        
        int GetHP() const {
            
            return m_hp;
        }
        
        int GetMaxHP() const {
            
            return m_maxHP;
        }
        
      private:
        void TryMoveToCoord(UserID userID, Point coord);
        
        std::string m_name {"Unnamed player"};
        Point m_coord {5, 5};                            ///< Coordinate on the current world area.
        std::optional<Point> m_destCoord {std::nullopt}; ///< Destination to which the player is moving.
        TimePoint m_ticksLastMove {Now()};               ///< Last time the player moved one step.
        float m_movementSpeed {5.0f};                    ///< Base movement speed.
        int m_experience {0};
        TimePoint m_ticksLastAttackOnOther {Now()};
        float m_attackSpeed {1.0f};
        int m_hp {10};
        int m_maxHP {10};
    };
}
/*
 * NPC.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class NPC {
      public:
        
        bool GetIsFollowingPath() const {
            
            return m_isFollowingPath;
        }
        
        void SetIsFollowingPath(bool isFollowingPath) {
            
            m_isFollowingPath = isFollowingPath;
        }
        
        TimePoint GetTicksLastMove() const {
            
            return m_ticksLastMove;
        }
        
        void SetTicksLastMove(TimePoint ticksLastMove) {
            
            m_ticksLastMove = ticksLastMove;
        }
        
        float GetMovementSpeed() const {
            
            return m_movementSpeed;
        }
        
      private:
        
        // Members
        
        bool m_isFollowingPath {false};
        
        TimePoint m_ticksLastMove {Now()};
        
        float m_movementSpeed {9.0f};
    };
}
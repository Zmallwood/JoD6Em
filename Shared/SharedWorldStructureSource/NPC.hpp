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
        
        TimePoint GetTimeLastMove() const {
            
            return m_timeLastMove;
        }
        
        void SetTimeLastMove(TimePoint timeLastMove) {
            
            m_timeLastMove = timeLastMove;
        }
        
        float GetMovementSpeed() const {
            
            return m_movementSpeed;
        }
        
      private:
        
        // Members
        
        bool m_isFollowingPath {false};
        
        TimePoint m_timeLastMove {Now()};
        
        float m_movementSpeed {9.0f};
    };
}
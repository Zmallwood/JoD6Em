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
    
    float GetMoveSpd() const {
        
        return m_moveSpd;
    }
    
    Timer& GetTimerMove() {
        
        return m_timerMove;
    }
    
  private:
    
    // Members
    
    bool m_isFollowingPath {false};
    
    float m_moveSpd {9.0f};
    
    Timer m_timerMove;
};

}
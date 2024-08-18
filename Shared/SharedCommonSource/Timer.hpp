/*
 * Timer.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "CommonAliases.hpp"

namespace JoD {

class Timer {
    
  public:
    
    bool Tick(float tickSpeed);
    
  private:
    
    TimePoint m_timeLastTick {Now()};
    
};

}
/*
 * Timer.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Timer.hpp"

namespace JoD {

bool Timer::Tick(float tickSpeed) {
    
    auto result = Now() >
                  m_timeLastTick +
                  Duration(Millis(static_cast<int>(1000/tickSpeed)));
    
    if (result) {
        
        m_timeLastTick = Now();
    }
    
    return result;
}

}
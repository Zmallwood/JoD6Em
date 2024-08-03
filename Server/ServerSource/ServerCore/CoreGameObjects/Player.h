/*
 * Player.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class player {
    public:
        point m_coordinate = {5, 5};
        point m_destination = {-1, -1};
        std::chrono::high_resolution_clock::time_point m_ticks_last_move = std::chrono::high_resolution_clock::now();
        float m_movement_speed {3.0f};
    };
}
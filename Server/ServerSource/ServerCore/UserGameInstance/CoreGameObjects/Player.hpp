/*
 * Player.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class Player {
      public:
        Point m_coordinate = {5, 5};
        Point m_destination = {-1, -1};
        TimePoint m_ticksLastMove = Now();
        float m_movementSpeed {3.0f};
    };
}
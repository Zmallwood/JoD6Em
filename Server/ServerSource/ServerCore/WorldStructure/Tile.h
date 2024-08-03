/*
 * Tile.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class creature;

    class tile {
    public:
        int m_ground = 0;
        int m_object = 0;
        std::shared_ptr<creature> m_creature;
    };
}
/*
 * WorldArea.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "WorldArea.h"
#include "Tile.h"

namespace JoD {
    WorldArea::WorldArea(){
        for (auto x = 0; x < 100; x++){
            m_tiles.push_back(std::vector<std::shared_ptr<Tile>>());
            for (auto y = 0; y < 100; y++)
                m_tiles.at(x).push_back(std::make_shared<Tile>());
        }
    }
}
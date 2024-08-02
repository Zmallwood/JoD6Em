// world_area.cpp
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
//

#include "world_area.h"
#include "tile.h"

namespace jod {
    world_area::world_area(){
        for (auto x = 0; x < 100; x++){
            m_tiles.push_back(std::vector<std::shared_ptr<tile> >());
            for (auto y = 0; y < 100; y++){
                m_tiles.at(x).push_back(std::make_shared<tile>());
            }
        }
    }
}
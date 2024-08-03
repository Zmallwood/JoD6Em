/*
 * WorldArea.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class tile;

    class world_area {
    public:
        world_area();
        
        std::vector<std::vector<std::shared_ptr<tile> > > m_tiles;
    };
}
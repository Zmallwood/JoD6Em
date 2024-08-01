// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod {
    class world_area;
    class tile;
    class creature;

    class world {
    public:
        world();
        
        std::shared_ptr<world_area> m_currentWorldArea;
    };

    class world_area {
    public:
        world_area();
        
        std::vector<std::vector<std::shared_ptr<tile> > > m_tiles;
    };

    class tile {
    public:
        int m_ground = 0;
        int m_object = 0;
        std::shared_ptr<creature> m_creature;
    };
    
    class creature {
    public:
        int m_type = 0;
    };
}
/*
 * WorldArea.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Configuration/GameProperties.hpp"

namespace JoD {
    
    WorldArea::WorldArea(){
        
        for (auto x = 0; x < _<GameProperties>().GetWorldAreaSize().w; x++){
            
            m_tiles.push_back(std::vector<std::shared_ptr<Tile>>());
            
            for (auto y = 0; y < _<GameProperties>().GetWorldAreaSize().h; y++) {
                
                m_tiles.at(x).push_back(std::make_shared<Tile>());
            }
        }
    }
    
    Size WorldArea::GetSize() const {
        
        const auto width = static_cast<int>(m_tiles.size());
        auto height = 0;
        
        if (m_tiles.size() > 0) {
            
            height = m_tiles.at(0).size();
        }
        
        return {width, height};
    }
    
    bool WorldArea::IsValidCoord(Point coord) const {
        
        const auto size = GetSize();
        
        return coord.x >= 0 && coord.y >= 0 && coord.x < size.w &&
               coord.y < size.h;
    }
}
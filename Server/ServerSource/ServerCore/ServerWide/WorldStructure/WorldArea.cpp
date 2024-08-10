/*
 * WorldArea.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "WorldArea.hpp"
#include "Configuration/GameProperties.hpp"
#include "Tile.hpp"

namespace JoD {
    
    struct WorldArea::Impl {
        std::vector<std::vector<std::unique_ptr<Tile>>> tiles; ///< Tile grid.
        std::map<std::shared_ptr<Mob>, Point>
        mobPositions; ///< Helper structure which maps mobs to their positions.
    };
    
    WorldArea::WorldArea()
    : m_pImpl(std::make_unique<Impl>()){
        
        for (auto x = 0; x < _<GameProperties>().GetWorldAreaSize().w; x++){
            
            m_pImpl->tiles.push_back(std::vector<std::unique_ptr<Tile>>());
            
            for (auto y = 0; y < _<GameProperties>().GetWorldAreaSize().h;
                 y++) {
                
                m_pImpl->tiles.at(x).push_back(std::make_unique<Tile>());
            }
        }
    }
    
    WorldArea::~WorldArea() {
        
    }
    
    Size WorldArea::GetSize() const {
        
        const auto width = static_cast<int>(m_pImpl->tiles.size());
        auto height = 0;
        
        if (m_pImpl->tiles.size() > 0) {
            
            height = m_pImpl->tiles.at(0).size();
        }
        
        return {width, height};
    }
    
    bool WorldArea::IsValidCoord(Point coord) const {
        
        const auto size = GetSize();
        
        return coord.x >= 0 && coord.y >= 0 && coord.x < size.w &&
               coord.y < size.h;
    }
    
    bool WorldArea::IsValidCoord(int x, int y) const {
        
        return IsValidCoord({x, y});
    }
    
    Tile* WorldArea::GetTile(Point coord) const {
        if (IsValidCoord(coord)) {
            
            return m_pImpl->tiles.at(coord.x).at(coord.y).get();
        }
        
        return nullptr;
    }
    
    Tile* WorldArea::GetTile(int xCoord, int yCoord) const {
        
        return GetTile({xCoord, yCoord});
    }
    
    void WorldArea::RegisterMobPosition(std::shared_ptr<Mob> mob, Point coord) {
        
        m_pImpl->mobPositions.insert({mob, coord});
    }
    
    void WorldArea::RemoveMobPosition(std::shared_ptr<Mob> mob) {
        
        if (m_pImpl->mobPositions.contains(mob)) {
            
            m_pImpl->mobPositions.erase(mob);
        }
    }
    
    std::optional<Point> WorldArea::GetMobCoord(std::shared_ptr<Mob> mob) const {
        
        if (m_pImpl->mobPositions.contains(mob)) {
            
            return m_pImpl->mobPositions.at(mob);
        }
        
        return std::nullopt;
    }
}
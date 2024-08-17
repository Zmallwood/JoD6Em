/*
 * WorldArea.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "WorldArea.hpp"
#include "Tile.hpp"
#include "WorldStructureConstants.hpp"

namespace JoD {

struct WorldArea::Impl {
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles; ///< Tile grid.
    std::map<std::shared_ptr<Creature>, Point>
    creaturePositions;                                     ///< Helper structure which maps creatures to their positions.
};

WorldArea::WorldArea()
    : m_pImpl(std::make_unique<Impl>()) {
    
    for (auto x = 0; x < WorldStructureConstants::k_worldAreaSize.w; x++){
        
        m_pImpl->tiles.push_back(std::vector<std::unique_ptr<Tile>>());
        
        for (auto y = 0; y < WorldStructureConstants::k_worldAreaSize.h;
             y++) {
            
            m_pImpl->tiles.at(x).push_back(std::make_unique<Tile>());
        }
    }
}

WorldArea::~WorldArea() {}

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

void WorldArea::RegisterCreaturePosition(std::shared_ptr<Creature> creature,
                                         Point coord) {
    
    m_pImpl->creaturePositions.insert({creature, coord});
}

void WorldArea::RemoveCreaturePosition(std::shared_ptr<Creature> creature) {
    
    if (m_pImpl->creaturePositions.contains(creature)) {
        
        m_pImpl->creaturePositions.erase(creature);
    }
}

std::optional<Point> WorldArea::GetCreatureCoord(
    std::shared_ptr<Creature> creature) const {
    
    if (m_pImpl->creaturePositions.contains(creature)) {
        
        return m_pImpl->creaturePositions.at(creature);
    }
    
    return std::nullopt;
}

const std::map<std::shared_ptr<Creature>,
               Point>& WorldArea::GetCreaturePositions() const {
    
    return m_pImpl->creaturePositions;
}

}
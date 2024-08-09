/*
 * GameProperties.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GameProperties.hpp"

namespace JoD {
    
    struct GameProperties::Impl {
        const int k_numGridRows {21};         ///< Number of rows in tile grid in world view.
        const Size k_worldAreaSize {100, 100};
    };
    
    GameProperties::GameProperties() : m_pImpl(std::make_unique<Impl>()){
    }
    
    GameProperties::~GameProperties() {
        
    }
    
    int GameProperties::GetNumGridRows() const {
        
        return m_pImpl->k_numGridRows;
    }
    
    Size GameProperties::GetWorldAreaSize() const {
        
        return m_pImpl->k_worldAreaSize;
    }
}
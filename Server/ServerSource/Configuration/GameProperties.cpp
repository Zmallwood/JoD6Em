/*
 * GameProperties.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GameProperties.hpp"

namespace JoD {

struct GameProperties::Impl {
    
    const int k_numGridRows {11};              // Number of rows in tile grid in world view.
};

GameProperties::GameProperties()
    : m_pImpl(std::make_unique<Impl>()) {}

GameProperties::~GameProperties() {}

int GameProperties::GetNumGridRows() const {
    
    return m_pImpl->k_numGridRows;
}

}
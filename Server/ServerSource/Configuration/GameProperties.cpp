/*
 * GameProperties.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GameProperties.hpp"

namespace JoD {
struct GameProperties::Impl {
// Number of rows in tile grid in world view.
    const int k_numGridRows {11};
};

GameProperties::GameProperties()
    : m_pImpl(std::make_unique<Impl>()) {}

GameProperties::~GameProperties() {}

int GameProperties::GetNumGridRows() const {
// Return nr of grid rows in tile grid in world view.
    return m_pImpl->k_numGridRows;
}
}

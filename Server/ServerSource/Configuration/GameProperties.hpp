/*
 * GameProperties.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
/// Holds game configuration parameters.
class GameProperties {
  public:
    /// Construct a new Game Properties object.
    GameProperties();
    
    /// Destroy the Game Properties object. Needed by PIMPL idiom.
    ~GameProperties();
    
    /// Get the number of grid rows in tile grid in WorldView.
    /// @return int Number of grid rows.
    int GetNumGridRows() const;
    
  private:
// PIMPL struct defined in source file.
    struct Impl;
    
 // PIMPL idiom used for compilation speed reasons.
    std::unique_ptr<Impl> m_pImpl;
};
}
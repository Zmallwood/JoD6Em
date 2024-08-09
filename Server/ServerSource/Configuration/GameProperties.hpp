/*
 * GameProperties.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include <experimental/propagate_const>

namespace JoD {
    
    ///
    /// Holds game configuration parameters.
    ///
    class GameProperties {
        
      public:
        GameProperties();
        
        ~GameProperties();
        
        int GetNumGridRows() const;
        
        Size GetWorldAreaSize() const;
        
      private:
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}
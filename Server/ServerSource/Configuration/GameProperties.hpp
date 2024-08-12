/*
 * GameProperties.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Holds game configuration parameters.
    ///
    class GameProperties {
        
      public:
        ///
        /// Construct a new Game Properties object
        ///
        GameProperties();
        
        ///
        /// Destroy the Game Properties object
        ///
        ~GameProperties();
        
        ///
        /// Get the number of grid rows in tile grid in WorldView.
        /// 
        /// @return int Number of grid rows.
        ///
        int GetNumGridRows() const;
        
        ///
        /// Get the size used to create new world areas.
        /// 
        /// @return Size World area size.
        ///
        Size GetWorldAreaSize() const;
        
      private:
        struct Impl; ///< PIMPL struct defined in source file.
        
        std::unique_ptr<Impl> m_pImpl; ///< PIMPL idiom used for compilation speed reasons.
    };
}
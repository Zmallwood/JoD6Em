/*
 * World.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class WorldArea;
    
    ///
    /// Top-level world object, of which only one (static)
    /// instance exists and is used for all connected users.
    ///
    class World {
        
      public:
      
        ///
        /// Construct a new World object by creating contained world area.
        ///
        World();
        
        ~World();
        
        WorldArea* GetCurrentWorldArea() const;
        
      private:
      
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}
/*
 * Tile.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class Mob;
    class Object;
    
    ///
    /// Represents a square tile in the game world.
    ///
    class Tile {
        
      public:
        Tile();
        
        ~Tile();
      
        int GetGround() const;
        
        void SetGround(int value);
        
        Object* GetObject() const;
        
        void SetObject(std::unique_ptr<Object> value);
        
        const std::shared_ptr<Mob> GetMob() const;
        
        void SetMob(std::shared_ptr<Mob> value) ;
        
      private:
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}
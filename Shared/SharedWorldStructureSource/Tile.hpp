/*
 * Tile.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class Creature;
class ObjectsPile;
class NPC;

///
/// Represents a square tile in the game world.
///
class Tile {
    
  public:
    
    Tile();
    
    ~Tile();
    
    int GetGround() const;
    
    void SetGround(int value);
    
    void SetGround(std::string_view imageName);
    
    const std::shared_ptr<Creature> GetCreature() const;
    
    void SetCreature(std::shared_ptr<Creature> value);
    
    int GetElevation() const;
    
    void SetElevation(int value);
    
    ObjectsPile &GetObjectsPile() const;
    
    std::shared_ptr<NPC> GetNPC() const;
    
    void SetNPC(std::shared_ptr<NPC> npc);
    
    Tile* GetAbove() const;
    
    void SetAbove(std::unique_ptr<Tile> above);
    
  private:
    
    struct Impl;
    
    std::unique_ptr<Impl> m_pImpl;
};

}
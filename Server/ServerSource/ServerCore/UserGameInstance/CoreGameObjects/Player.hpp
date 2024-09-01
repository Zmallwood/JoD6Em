/*
 * Player.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "CommonAliases.hpp"
#include "Directions.hpp"

namespace JoD {
/// Core player object, of which one is created for each connecting user.
class Player {
  public:
    
/// Try move played in a direction which will success if nothing is blocking.
/// @param userID User ID to which the Player object belongs.
/// @param direction Direction to move towards.
    void TryMove(UserID userID, Directions direction);
    
/// Inflict damage on player, decreases the players health points.
/// @param damage Amount of damage points to inflict, equals the damage decrease amount.
    void Hit(int damage);
    
/// Sets the players experience to zero.
    void ResetExp();
    
/// Add experience amount to players total experience.
/// @param value
    void AddExp(int value);
    
/// Get the name of the player.
/// @return std::string Player name.
    std::string GetName() const {
        return m_name;
    }
    
/// Get the coordinate of the player.
/// @return Point Player coordinate.
    Point GetCoord() const {
        return m_coord;
    }
    
/// Set the coordinate of the player.
/// @param coord New player coordinate.
    void SetCoord(Point coord) {
        m_coord = coord;
    }
    
/// Get the destination coordinate for the player.
/// @return std::optional<Point> Destination coordinate of player.
    std::optional<Point> GetDestCoord() const {
        return m_destCoord;
    }
    
/// Set the destination coordinate for the player.
/// @param value New destination coordinate.
    void SetDestCoord(std::optional<Point> value) {
        m_destCoord = value;
    }
    
/// Get time point when player last moved.
/// @return TimePoint Time point when player last moved.
    TimePoint GetTimeLastMove() const {
        return m_timeLastMove;
    }
    
/// Set the time point when player last moved.
/// @param value New time point value.
    void SetTimeLastMove(TimePoint value) {
        m_timeLastMove = value;
    }
    
/// Get the movement speed of the player.
/// @return float Player movement speed.
    float GetMoveSpd() const {
        return m_moveSpd;
    }
    
/// Get the amount of experience the player has.
/// @return float Player experience amount.
    float GetExp() const {
        return m_exp;
    }
    
/// Get the time point for when the player last attacked another.
/// @return TimePoint Time point when player last attacked another.
    Timer& GetTimerAttackOnOther() {
        return m_timerAttackOnOther;
    }
    
/// Get the players attack speed.
/// @return float Player attack speed.
    float GetAtkSpd() const {
        return m_atkSpd;
    }
    
/// Get the players current health points.
/// @return int Player health points.
    int GetHP() const {
        return m_hp;
    }
    
/// Sets the players current hit points value.
/// @param hp New health poins value.
    void SetHP(int hp) {
        m_hp = hp;
    }
    
/// Get the player maximum amount of health points.
/// @return int Players maximum health points value.
    int GetMaxHP() const {
        return m_maxHP;
    }
    
    TimePoint GetTimeSetDest() const {
        return m_timeSetDest;
    }
    
    void SetTimeSetDest(TimePoint timeSetDest) {
        m_timeSetDest = timeSetDest;
    }
    
    int GetWorldFloor() const {
        return m_worldFloor;
    }
    
    void IncreaseWorldFloor(int amount = 1) {
        m_worldFloor += amount;
    }
    
  private:
    
/// Tries to move the player to a specific coordinate. Will succeed
/// only if the destination tile is walkable.
/// @param userID User ID for which player that is attempted to move.
/// @param coord Coordinate to try to move to.
    void TryMoveToCoord(UserID userID, Point coord);
    
// Player name.
    std::string m_name {"Unnamed player"};           
// Coordinate on the current world area.
    Point m_coord {5, 5};  
    int m_worldFloor {0};                          
// Destination to which the player is moving.
    std::optional<Point> m_destCoord {std::nullopt}; 
// Last time the player moved one step.
    TimePoint m_timeLastMove {Now()};                
// Base movement speed.
    float m_moveSpd {5.0f};                               
// Player total experience amount.
    int m_exp {0};                            
// Player attack speed.
    float m_atkSpd {1.0f};                      
// Timer for when player is attacking another.
    Timer m_timerAttackOnOther;
// Players current health points.
    int m_hp {10};                                   
// Players maximum amount of health points.
    int m_maxHP {10};    
    TimePoint m_timeSetDest {Now()};                            
};
}

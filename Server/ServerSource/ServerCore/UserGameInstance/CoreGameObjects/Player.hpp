/*
 * Player.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Core player objects, of which one is created for each connecting user.
    ///
    class Player {
        
      public:
        void TryMoveNorth();
        
        void TryMoveEast();
        
        void TryMoveSouth();
        
        void TryMoveWest();
        
        void TryMoveNorthEast();
        
        void TryMoveSouthEast();
        
        void TryMoveSouthWest();
        
        void TryMoveNorthWest();
        
        Point Coord() const {
            
            return m_coord;
        }
        
        std::optional<Point> DestCoord() const {
            
            return m_destCoord;
        }
        
        void SetDestCoord(std::optional<Point> value) {
            
            m_destCoord = value;
        }
        
        TimePoint TicksLastMove() const {
            
            return m_ticksLastMove;
        }
        
        void SetTicksLastMove(TimePoint value) {
            
            m_ticksLastMove = value;
        }
        
        float MovementSpeed() const {
            
            return m_movementSpeed;
        }
        
      private:
        void TryMoveToCoord(Point coord);
        
        Point m_coord {5, 5}; ///< Coordinate on the current world area.
        std::optional<Point> m_destCoord {std::nullopt}; ///< Destination to which the player is moving.
        TimePoint m_ticksLastMove {Now()}; ///< Last time the player moved one step.
        float m_movementSpeed {5.0f}; ///< Base movement speed.
    };
}
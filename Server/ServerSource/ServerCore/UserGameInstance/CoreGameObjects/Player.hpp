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
        
        Point m_coordinate {5, 5}; ///< Coordinate on the current world area.
        Point m_destination {-1, -1}; ///< Destination to which the player is moving.
        TimePoint m_ticksLastMove {Now()}; ///< Last time the player moved one step.
        float m_movementSpeed {5.0f}; ///< Base movement speed.
        
      private:
        void TryMoveToCoord(Point coord);
    };
}
/*
 * Player.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "Directions.hpp"

namespace JoD {

    ///
    /// Core player object, of which one is created for each connecting user.
    ///
    class Player {

      public:

        ///
        /// Try move played in a direction which will success if nothing is blocking.
        /// 
        /// @param userID User ID to which the Player object belongs.
        /// @param direction Direction to move towards.
        ///
        void TryMove(UserID userID, Directions direction);

        ///
        /// Inflict damage on player, decreases the players health points.
        /// 
        /// @param damage Amount of damage points to inflict, equals the damage decrease amount.
        ///
        void Hit(int damage);

        ///
        /// Get the name of the player.
        /// 
        /// @return std::string Player name.
        ///
        std::string GetName() const {

            return m_name;
        }
        
        ///
        /// Get the coordinate of the player.
        /// 
        /// @return Point Player coordinate.
        ///
        Point GetCoord() const {

            return m_coord;
        }

        ///
        /// Set the coordinate of the player.
        /// 
        /// @param coord New player coordinate.
        ///
        void SetCoord(Point coord) {

            m_coord = coord;
        }

        ///
        /// Get the destination coordinate for the player.
        /// 
        /// @return std::optional<Point> Destination coordinate of player.
        ///
        std::optional<Point> GetDestCoord() const {

            return m_destCoord;
        }

        ///
        /// Set the destination coordinate for the player.
        /// 
        /// @param value New destination coordinate.
        ///
        void SetDestCoord(std::optional<Point> value) {

            m_destCoord = value;
        }

        TimePoint GetTimeLastMove() const {

            return m_timeLastMove;
        }

        void SetTimeLastMove(TimePoint value) {

            m_timeLastMove = value;
        }

        float GetMovementSpeed() const {

            return m_movementSpeed;
        }

        float GetExperience() const {

            return m_experience;
        }

        void ResetExperience() {

            m_experience = 0;
        }

        void AddExperience(int value) {

            m_experience += value;
        }

        TimePoint GetTimeLastAttackOnOther() const {

            return m_timeLastAttackOnOther;
        }

        void SetTimeLastAttackOnOther(TimePoint value) {

            m_timeLastAttackOnOther = value;
        }

        float GetAttackSpeed() const {

            return m_attackSpeed;
        }

        int GetHP() const {

            return m_hp;
        }

        void SetHP(int hp) {

            m_hp = hp;
        }

        int GetMaxHP() const {

            return m_maxHP;
        }

      private:

        void TryMoveToCoord(UserID userID, Point coord);

        // Members

        std::string m_name {"Unnamed player"};

        Point m_coord {5, 5};                            ///< Coordinate on the current world area.

        std::optional<Point> m_destCoord {std::nullopt}; ///< Destination to which the player is moving.

        TimePoint m_timeLastMove {Now()};               ///< Last time the player moved one step.

        float m_movementSpeed {5.0f};                    ///< Base movement speed.

        int m_experience {0};

        TimePoint m_timeLastAttackOnOther {Now()};

        float m_attackSpeed {1.0f};

        int m_hp {10};

        int m_maxHP {10};
    };
}

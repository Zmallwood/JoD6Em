/*
 * Creature.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "CommonAliases.hpp"
#include "CreatureMaturity.hpp"
#include "Object.hpp"

namespace JoD {

struct ConnectedObject {
    
    std::shared_ptr<Object> connectedObject;
    Point objectCoord;
};

///
/// Combatable creature object which can be positioned on a tile.
///
class Creature {
    
  public:
    ///
    /// Construct a new Creature object.
    ///
    /// @param creatureName Creature type name.
    /// @param level Initial level, determines all the stats of the creature.
    ///
    Creature(std::string_view creatureName, int level);
    
    ///
    /// Hit the creature for a certain amount of damage.
    ///
    /// @param damage Damage to hit with, will result in a hp decrease by the same amount.
    ///
    void Hit(int damage);
    
    ///
    /// Get the creature type.
    ///
    /// @return int Creature type.
    ///
    int GetType() const {
        
        return m_type;
    }
    
    ///
    /// Get the creature level.
    ///
    /// @return int Creature level.
    ///
    int GetLevel() const {
        
        return m_level;
    }
    
    ///
    /// Get the creature health points.
    ///
    /// @return int Creature health points.
    ///
    int GetHP() const {
        
        return m_hp;
    }
    
    ///
    /// Get the amount of experience gained when defeating this creature.
    ///
    /// @return int Exp gain value.
    ///
    int GetExp() const {
        
        return m_exp;
    }
    
    ///
    /// Get the timepoint for when this creature last got hit by another.
    ///
    /// @return TimePoint Last time hit by another.
    ///
    TimePoint GetTimeLastHitFromOther() const {
        
        return m_timeLastHitFromOther;
    }
    
    ///
    /// Tells if this creature is dead.
    ///
    /// @return true If dead.
    /// @return false If alive.
    ///
    bool IsDead() const;
    
    UserID GetTargetedUserID() const {
        
        return m_targetedUserID;
    }
    
    void SetTargetedUserID(UserID userID) {
        
        m_targetedUserID = userID;
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
    
    void SetConnectedObject(ConnectedObject connectedObject) {
        
        m_connectedObject =
            std::make_unique<ConnectedObject>(
                connectedObject.connectedObject,
                connectedObject.objectCoord);
    }
    
    bool GetIsFollowingPath() const {
        
        return m_isFollowingPath;
    }
    
    void SetIsFollowingPath(bool isFollowingPath) {
        
        m_isFollowingPath = isFollowingPath;
    }
    
    TimePoint GetTimeLastMove() const {
        
        return m_timeLastMove;
    }
    
    void SetTimeLastMove(TimePoint timeLastMove) {
        
        m_timeLastMove = timeLastMove;
    }
    
    float GetMS() const {
        
        return m_ms;
    }
    
    ConnectedObject* GetConnectedObject() const {
        
        return m_connectedObject.get();
    }
    
  private:
    
    // Members
    
    int m_type {0};                                         ///< Hash code of creature type name.
    
    int m_level {0};                                        ///< Level, as provided in ctor.
    
    int m_pAtk {0};                                         ///< Physical attack.
    
    int m_mAtk {0};                                         ///< Magic attack.
    
    int m_pDef {0};                                         ///< Physical defense.
    
    int m_mDef {0};                                         ///< Magic defense.
    
    float m_atkSpeed {0};                                   ///< Attack speed.
    
    int m_hp {0};                                           ///< Health points.
    
    int m_exp {0};                                          ///< Experience gained when defeating this creature.
    
    TimePoint m_timeLastHitFromOther {Now()};               ///< TimePoint for when this creature was last hit by another.
    
    CreatureMaturity m_maturity {CreatureMaturity::Mature}; ///< Specifies the maturity/aging of this creature.
    
    UserID m_targetedUserID {0};
    
    TimePoint m_timeLastAttackOnOther {Now()};
    
    float m_attackSpeed {1.0f};
    
    std::unique_ptr<ConnectedObject> m_connectedObject;
    
    bool m_isFollowingPath {false};
    
    TimePoint m_timeLastMove {Now()};
    
    float m_ms {6.0f};
};

}
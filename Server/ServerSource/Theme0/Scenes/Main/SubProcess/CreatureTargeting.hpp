/*
 * CreatureTargeting.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "IMainSceneComponent.hpp"

namespace JoD {
class Creature;
/// Enables targeting creatures in the game world by right clicking on them.
class CreatureTargeting : public IMainSceneComponent {
  public:
    /// Use base ctor.
    using IMainSceneComponent::IMainSceneComponent;
    
    /// Override base class method.
    /// @param userID User ID for user which this component belongs to.
    void Update(UserID userID) override;
    
    /// Get the currently targeted creature.
    /// @return std::shared_ptr<Creature> Targeted creature.
    std::shared_ptr<Creature> GetTargetedCreature() const {
        return m_targetedCreature;
    }
    
    /// Set the currently targeted creature.
    /// @param value New targeted creature.
    void SetTargetedCreature(std::shared_ptr<Creature> value) {
        m_targetedCreature = value;
    }
    
  private:
// Currently targeted creature, nullptr means no target.
    std::shared_ptr<Creature>
    m_targetedCreature;
};
}

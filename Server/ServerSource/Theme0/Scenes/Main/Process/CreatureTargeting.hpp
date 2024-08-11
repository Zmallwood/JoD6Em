/*
 * CreatureTargeting.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "IMainSceneComponent.hpp"

namespace JoD {
    
    class Creature;
    
    ///
    /// Enables targeting creatures in the game world by right clicking on them.
    ///
    class CreatureTargeting : public IMainSceneComponent {
        
      public:
        ///
        /// Use base ctor.
        ///
        using IMainSceneComponent::IMainSceneComponent;
        
        ///
        /// Override base class method.
        ///
        void Update(UserID userID) override;
        
        std::shared_ptr<Creature> GetTargetedCreature() const {
            
            return m_targetedCreature;
        }
        
        void SetTargetedCreature(std::shared_ptr<Creature> value) {
            
            m_targetedCreature = value;
        }
        
      private:
        std::shared_ptr<Creature>
        m_targetedCreature; ///< Currently targeted creature, nullptr means no target.
    };
}
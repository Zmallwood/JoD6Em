/*
 * MobTargeting.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "IMainSceneComponent.hpp"

namespace JoD {
    
    class Mob;
    
    ///
    /// Enables targeting mobs in the game world by right clicking on them.
    ///
    class MobTargeting : public IMainSceneComponent {
        
      public:
        ///
        /// Use base ctor.
        ///
        using IMainSceneComponent::IMainSceneComponent;
        
        ///
        /// Override base class method.
        ///
        void Update(UserID userID) override;
        
        std::shared_ptr<Mob> TargetedCreature() const {
            
            return m_targetedCreature;
        }
        
        void SetTargetedCreature(std::shared_ptr<Mob> value) {
            
            m_targetedCreature = value;
        }
        
      private:
        std::shared_ptr<Mob>
        m_targetedCreature; ///< Currently targeted creature, nullptr means no target.
    };
}
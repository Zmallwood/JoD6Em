/*
 * MobTargeting.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "IMainSceneComponent.hpp"

namespace JoD {
    
    class Mob;
    
    class MobTargeting : public IMainSceneComponent {
        
      public:
        using IMainSceneComponent::IMainSceneComponent;
        
        void Update() override;
        
        std::shared_ptr<Mob> m_targetedCreature;
    };
}
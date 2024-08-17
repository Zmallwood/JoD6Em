/*
 * Combat.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "IMainSceneComponent.hpp"

namespace JoD {

class Combat : public IMainSceneComponent {
    
  public:
    
    using IMainSceneComponent::IMainSceneComponent;
    
    void Update(UserID userID) override;
};

}

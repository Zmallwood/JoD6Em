/*
 * LoginScene.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "ServerCore/UserGameInstance/ScenesCore/IScene.hpp"

namespace JoD {
class LoginScene : public IScene {
  public:
    void Initialize(UserID userID) override;
    
  protected:
    void RenderDerived(UserID userID) const override;
};
}

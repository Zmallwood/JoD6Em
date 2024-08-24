/*
 * RegisterScene.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "ServerCore/UserGameInstance/ScenesCore/IScene.hpp"

namespace JoD {
class GUITextBox;

class RegisterScene : public IScene {
  public:
    void Initialize(UserID userID) override;
    
  protected:
    void RenderDerived(UserID userID) const override;
    
  private:
    void RegisterNewUser();
    
    std::shared_ptr<GUITextBox> m_usernameTextBox;
    std::shared_ptr<GUITextBox> m_passwordTextBox;
};
}


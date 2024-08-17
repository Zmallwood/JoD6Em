/*
 * GUITextConsole.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/GUICore/GUIPanel.hpp"

namespace JoD {

class GUITextConsole : public GUIPanel {
    
  public:
    
    GUITextConsole();
    
    void RenderDerived(UserID userID) const override;
    
  private:
    
    // Members
    
    static constexpr float k_width {0.35f};
    
    static constexpr float k_height {0.2f};
    
    static constexpr float k_lineHeight {0.02f};
    
    static constexpr float k_margin {0.005f};
};

}

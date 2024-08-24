/*
 * GUITextBox.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "GUIComponent.hpp"
#include "ManagedString.hpp"

namespace JoD {
class GUITextBox : public GUIComponent {
  public:
    GUITextBox(BoxF bounds, GUIComponent *parent = nullptr);
    
    void UpdateDerived(UserID userID) override;
    
    void RenderDerived(UserID userID) const override;
    
  private:
    BoxF GetBounds() const;
    
    SizeF m_size;
    ManagedString m_text;
    const float k_cursorWidth {0.005f};
};
}

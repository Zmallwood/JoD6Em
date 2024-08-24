/*
 * GUITextBox.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "GUIComponent.hpp"

namespace JoD {
class GUITextBox : public GUIComponent {
  public:
    GUITextBox(BoxF bounds);
    
    void RenderDerived(UserID userID) const override;
    
  private:
    BoxF GetBounds() const;
    
    SizeF m_size;
};
}

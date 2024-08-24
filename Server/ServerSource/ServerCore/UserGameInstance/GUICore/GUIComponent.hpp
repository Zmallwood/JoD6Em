/*
 * GUIComponent.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
class GUI;

/// Root base class for all inheriting GUI component types.
class GUIComponent {
  public:
/// Construct a new GUIComponent object.
/// @param position Position where the component is located on the canvas.
    GUIComponent(PointF position,
                 GUIComponent *parent = nullptr);
    
/// Update the component.
/// @param userID User ID for which user GUI the component belongs to.
    void Update(UserID userID);
    
/// Render the component.
/// @param userID User ID for which user GUI the component belongs to.
    void Render(UserID userID) const;
    
/// To be overridden by inheriting classes.
/// @param userID User ID for which user GUI the component belongs to.
    virtual void UpdateDerived(UserID userID) {}
    
/// To be overridden by inheriting classes.
/// @param userID User ID for which user GUI the component belongs to.
    virtual void RenderDerived(UserID userID) const {}
    
/// Set the visibility state.
/// @param value New visibility state value.
    void SetVisible(bool value) {
        m_visible = value;
    }
    
    GUIComponent *GetParent() const {
        return m_parent;
    }
    
    GUI *GetRootGUI() const;
    
  protected:
    std::vector<std::shared_ptr<GUIComponent>> &GetChildComponents() {
        return m_childComponents;
    }
    
// Position of component in canvas.
    PointF m_position;
// Visibility state.
    bool m_visible {true};
    
  private:
    std::vector<std::shared_ptr<GUIComponent>> m_childComponents;
    GUIComponent *m_parent = nullptr;
};
}

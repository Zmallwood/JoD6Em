/*
 * GUIComponent.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Root base class for all inheriting GUI component types.
///
class GUIComponent {
    
  public:
    
    ///
    /// Construct a new GUIComponent object.
    ///
    /// @param position Position where the component is located on the canvas.
    ///
    GUIComponent(PointF position);
    
    //////
    /// 
    /// 
    /// @param userID 
    ///
    ///
    /// @param userID User ID for which user GUI the component belongs to.
    ///
    void Update(UserID userID);
    
    ///
    /// Render the component.
    ///
    /// @param userID User ID for which user GUI the component belongs to.
    ///
    void Render(UserID userID) const;
    
    ///
    /// To be overridden by inheriting classes.
    ///
    /// @param userID User ID for which user GUI the component belongs to.
    ///
    virtual void UpdateDerived(UserID userID) {}
    
    ///
    /// To be overridden by inheriting classes.
    ///
    /// @param userID User ID for which user GUI the component belongs to.
    ///
    virtual void RenderDerived(UserID userID) const {}
    
    ///
    /// Set the visibility state.
    ///
    /// @param value New visibility state value.
    ///
    void SetVisible(bool value) {
        
        m_visible = value;
    }
    
  protected:
    
    // Members
    
    PointF m_position;         ///< Position of component in canvas.
    
    bool m_visible {true};     ///< Visibility state.
};

}

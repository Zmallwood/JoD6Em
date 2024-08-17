/*
 * GUIPanel.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "GUIComponent.hpp"

namespace JoD {
    
    ///
    /// A panel in the GUI with an image background.
    ///
    class GUIPanel : public GUIComponent {
        
      public:
        
        ///
        /// Construct a new GUIPanel object.
        ///
        /// @param bounds Bounds in which the background image is rendered.
        ///
        GUIPanel(BoxF bounds);
        
        ///
        /// Draw the background image of the panel.
        ///
        /// @param userID User ID for which user GUI the panel belongs to.
        ///
        void RenderDerived(UserID userID) const override;
        
      private:
        
        ///
        /// Get the bounds of the panel.
        ///
        /// @return BoxF Panel bounds.
        ///
        BoxF GetBounds() const;
        
        // Members
        
        SizeF m_size; ///< Size of the panel in canvas.
    };
}

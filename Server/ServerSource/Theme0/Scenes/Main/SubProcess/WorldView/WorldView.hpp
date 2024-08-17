/*
 * WorldView.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "Theme0/Scenes/Main/SubProcess/IMainSceneComponent.hpp"

namespace JoD {

///
/// Core component, rendered the world as a 2D tile grid.
///
class WorldView : public IMainSceneComponent {
    
  public:
    
    ///
    /// Use default ctor.
    ///
    using IMainSceneComponent::IMainSceneComponent;
    
    ///
    /// Renders the world to canvas as a 2D tile grid.
    ///
    /// @param webSocket Web socket associated with user.
    ///
    void Render(UserID userID) const override;
};

}

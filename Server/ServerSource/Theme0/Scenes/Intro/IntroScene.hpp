/*
 * IntroScene.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/ScenesCore/IScene.hpp"

namespace JoD {
    
    ///
    /// The first scene presented to the user on game start.
    ///
    class IntroScene : public IScene {
        
      public:
        ///
        /// Use base class ctor.
        ///
        using IScene::IScene;
        
      protected:
        ///
        /// Update game logic.
        ///
        void UpdateDerived() override;
        
        ///
        /// Render the scene to canvas.
        ///
        /// @param webSocket Web socket object for user.
        ///
        void RenderDerived(WebSocket &webSocket) const override;
    };
}
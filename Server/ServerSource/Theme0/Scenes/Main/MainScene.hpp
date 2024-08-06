/*
 * MainScene.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/ScenesCore/IScene.hpp"
#include "Process/MainSceneComponents.hpp"
#include "Process/IMainSceneComponent.hpp"

namespace JoD {
    
    ///
    /// The main scene where the playing takes place.
    ///
    class MainScene : public IScene {
        
      public:
        ///
        /// Use base class ctor.
        ///
        using IScene::IScene;
        
        std::map<MainSceneComponents, std::shared_ptr<IMainSceneComponent>>
        m_components; ///< Contains sub components for the scene.
        
      protected:
        ///
        /// Adds components to the scene.
        ///
        void Initialize() override;
        
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
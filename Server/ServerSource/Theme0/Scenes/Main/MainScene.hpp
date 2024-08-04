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
    class MainScene : public IScene {
    public:
        using IScene::IScene;

        std::map<MainSceneComponents,
                 std::shared_ptr<IMainSceneComponent>> m_components;
        
    protected:
        void Initialize() override;
        
        void UpdateDerived() override;
        
        void RenderDerived(WebSocket &webSocket) override;
    };
}
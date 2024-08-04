/*
 * IntroScene.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/ScenesCore/IScene.hpp"

namespace JoD {
    class IntroScene : public IScene {
    public:
        using IScene::IScene;
        
    protected:
        void UpdateDerived() override;
        
        void RenderDerived(WebSocket &webSocket) override;
    };
}
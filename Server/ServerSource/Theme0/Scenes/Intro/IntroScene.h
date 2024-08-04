/*
 * IntroScene.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/ScenesCore/IScene.h"

namespace JoD {
    class IntroScene : public IScene {
    protected:
        using IScene::IScene;
        
        void UpdateDerived() override;
        
        void RenderDerived(WebSocket &webSocket) override;
    };
}
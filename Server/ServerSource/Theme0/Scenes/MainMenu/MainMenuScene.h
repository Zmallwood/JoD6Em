/*
 * MainMenuScene.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/ScenesCore/IScene.h"

namespace jod {
    class MainMenuScene : public IScene {
    protected:
        using IScene::IScene;
        
        void UpdateDerived() override;
        void RenderDerived(boost::beast::websocket::stream<boost::asio::ip::
                                                    tcp::socket> &webSocket) override;
    };
}
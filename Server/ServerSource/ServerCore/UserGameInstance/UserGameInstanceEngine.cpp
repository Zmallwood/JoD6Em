/*
 * UserGameInstanceEngine.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */


#include "UserGameInstanceEngine.hpp"
#include "Input/Mouse/MouseInput.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/Cursor/Cursor.hpp"
#include "ScenesCore/SceneManager.hpp"
#include "ServerFPSCounter.hpp"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace JoD {
    
    UserGameInstanceEngine::UserGameInstanceEngine(
        UserConnection &userConnection)
        : m_userConnection(userConnection),
        m_sceneManager(std::make_shared<SceneManager>(userConnection)),
        m_mouseInput(std::make_shared<MouseInput>()),
        m_serverFPSCounter(std::make_shared<ServerFPSCounter>(userConnection)){
        
    }
    
    void UserGameInstanceEngine::Update() {
        
        m_sceneManager->UpdateCurrentScene();
        
        m_serverFPSCounter->Update();
    }
    
    void UserGameInstanceEngine::Render(WebSocket &ws) const {
        
        m_sceneManager->RenderCurrentScene(ws);
        
        m_serverFPSCounter->Render(ws);
        
        m_userConnection.m_cursor->Render(ws);
        
        m_userConnection.SendPresentCanvasInstruction(ws);
    }
}
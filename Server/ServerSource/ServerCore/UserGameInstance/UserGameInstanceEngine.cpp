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
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace JoD {
    
    UserGameInstanceEngine::UserGameInstanceEngine(
        UserConnection &userConnection)
        : m_userConnection(userConnection),
        m_sceneManager(std::make_shared<SceneManager>(userConnection)),
        m_mouseInput(std::make_shared<MouseInput>()),
        m_serverFPSCounter(std::make_shared<ServerFPSCounter>(userConnection)),
        m_player(std::make_shared<Player>()),
        m_cursor(std::make_shared<Cursor>(userConnection)){
        
    }
    
    void UserGameInstanceEngine::Update() {
        
        m_sceneManager->UpdateCurrentScene();
        
        m_serverFPSCounter->Update();
    }
    
    void UserGameInstanceEngine::Render(WebSocket &webSocket) const {
        
        m_sceneManager->RenderCurrentScene(webSocket);
        
        m_serverFPSCounter->Render(webSocket);
        
        m_cursor->Render(webSocket);
        
        m_userConnection.SendPresentCanvasInstruction(webSocket);
    }
    
    float UserGameInstanceEngine::GetAspectRatio() const {
        
        return static_cast<float>(m_canvasSize.w) / m_canvasSize.h;
    }
}
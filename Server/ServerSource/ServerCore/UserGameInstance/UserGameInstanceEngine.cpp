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
        UserConnection &user_connection)
        : m_user_connection(user_connection),
        m_scene_manager(std::make_shared<SceneManager>(user_connection)),
        m_mouse_input(std::make_shared<MouseInput>()),
        m_server_fps_counter(std::make_shared<ServerFPSCounter>(user_connection)){
    }
    
    void UserGameInstanceEngine::Update() {
        m_scene_manager->UpdateCurrentScene();
        m_server_fps_counter->Update();
    }
    
    void UserGameInstanceEngine::Render(WebSocket &ws) {
        m_scene_manager->RenderCurrentScene(ws);
        m_server_fps_counter->Render(ws);
        m_user_connection.m_cursor->Render(ws);
        m_user_connection.SendPresentCanvasInstruction(ws);
    }
}
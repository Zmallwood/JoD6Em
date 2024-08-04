/*
 * UserGameInstanceEngine.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */


#include "UserGameInstanceEngine.h"
#include "Input/Mouse/MouseInput.h"
#include "ServerCore/Net/UserConnection.h"
#include "ServerCore/UserGameInstance/Cursor/Cursor.h"
#include "ScenesCore/SceneManager.h"
#include "ServerFPSCounter.h"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace jod {
    user_game_instance_engine::user_game_instance_engine(
        user_connection &user_connection)
        : m_user_connection(user_connection),
        m_scene_manager(std::make_shared<scene_manager>(user_connection)),
        m_mouse_input(std::make_shared<mouse_input>()),
        m_server_fps_counter(std::make_shared<server_fps_counter>(user_connection)){
    }
    
    void user_game_instance_engine::update() {
        m_scene_manager->update_current_scene();
        m_server_fps_counter->update();
    }
    
    void user_game_instance_engine::render(WebSocket &ws) {
        m_scene_manager->render_current_scene(ws);
        m_server_fps_counter->render(ws);
        m_user_connection.m_cursor->render(ws);
        m_user_connection.send_present_canvas_instruction(ws);
    }
}
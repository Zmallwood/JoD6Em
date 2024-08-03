/*
 * ServerEngine.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ServerEngine.h"
#include "Input/Mouse/MouseInput.h"
#include "ServerCore/Net/UserConnection.h"
#include "ServerCore/UserGameInstance/Cursor/Cursor.h"
#include "ScenesCore/SceneManager.h"
#include "FPSCounter.h"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace jod {
    server_engine::server_engine(user_connection &user_connection)
        : m_user_connection(user_connection),
        m_scene_manager(std::make_shared<scene_manager>(user_connection)),
        m_mouse_input(std::make_shared<mouse_input>()),
        m_fps_counter(std::make_shared<fps_counter>(user_connection)){
    }
    
    void server_engine::update()      {
        m_scene_manager->update_current_scene();
        m_fps_counter->update();
    }
    
    void server_engine::render(websocket::stream<tcp::socket> &ws)      {
        m_scene_manager->render_current_scene(ws);
        m_fps_counter->render(ws);
        m_user_connection.m_cursor->render(ws);
        m_user_connection.send_present_canvas_instruction(ws);
    }
}
/*
 * server_engine.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "server_engine.h"
#include "input/mouse/mouse_input.h"
#include "server_core/net/user_connection.h"
#include "server_core/cursor/cursor.h"
#include "scenes_core/scene.h"
#include "scenes_core/scene_manager.h"
#include "fps_counter.h"

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
    
    void server_engine::on_key_down()      {
        m_scene_manager->on_key_down_current_scene();
    }
    
    void server_engine::on_mouse_down()      {
        m_scene_manager->on_mouse_down_current_scene();
    }
}
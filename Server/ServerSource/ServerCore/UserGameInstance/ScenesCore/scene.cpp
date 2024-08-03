/*
 * scene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "scene.h"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace jod {
    scene::scene(
        std::function<void()> update_action,
        std::function<void(websocket::stream<tcp::socket> &)> render_action,
        std::function<void()> key_down_action,
        std::function<void()> mouse_down_action)
        : m_update_action(update_action), m_render_action(render_action),
        m_key_down_action(key_down_action), m_mouse_down_action(mouse_down_action){
    }
    
    void
    scene::update(){
        m_update_action();
    }
    
    void
    scene::render(websocket::stream<tcp::socket> &ws){
        m_render_action(ws);
    }
    
    void
    scene::on_key_down(){
        m_key_down_action();
    }
    
    void
    scene::on_mouse_down(){
        m_mouse_down_action();
    }
}

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
        std::function<void()> updateAction,
        std::function<void(websocket::stream<tcp::socket> &)> renderAction,
        std::function<void()> keyDownAction,
        std::function<void()> mouseDownAction)
        : m_updateAction(updateAction), m_renderAction(renderAction),
        m_keyDownAction(keyDownAction), m_mouseDownAction(mouseDownAction){
    }
    
    void
    scene::update(){
        m_updateAction();
    }
    
    void
    scene::render(websocket::stream<tcp::socket> &ws){
        m_renderAction(ws);
    }
    
    void
    scene::on_key_down(){
        m_keyDownAction();
    }
    
    void
    scene::on_mouse_down(){
        m_mouseDownAction();
    }
}

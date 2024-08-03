/*
 * SceneManager.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "SceneManager.h"
#include "ServerCore/Net/UserConnection.h"
#include "Theme0/Scenes/Intro/IntroScene.h"
#include "Theme0/Scenes/MainMenu/MainMenuScene.h"
#include "Theme0/Scenes/WorldGeneration/WorldGenerationScene.h"
#include "Theme0/Scenes/Main/MainScene.h"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace jod {
    scene_manager::scene_manager(
        user_connection &user_connection) : m_user_connection(user_connection){
        
        m_scenes.insert(
            {jod::hash("IntroScene"),
             std::make_shared<IntroScene>(m_user_connection)});
        m_scenes.insert(
            {jod::hash("MainMenuScene"),
             std::make_shared<MainMenuScene>(m_user_connection)});
        m_scenes.insert(
            {jod::hash("WorldGenerationScene"),
             std::make_shared<WorldGenerationScene>(
                 m_user_connection)});
        m_scenes.insert(
            {jod::hash("MainScene"),
             std::make_shared<MainScene>(m_user_connection)});
        
        go_to("IntroScene");
    }
    
    void scene_manager::update_current_scene() {
        if (m_scenes.contains(m_current_scene))
            m_scenes.at(m_current_scene)->Update();
    }
    
    void scene_manager::render_current_scene(
        websocket::stream<tcp::socket> &ws) {
        if (m_scenes.contains(m_current_scene))
            m_scenes.at(m_current_scene)->Render(ws);
    }
    
    void scene_manager::go_to(std::string_view scene_name) {
        m_current_scene = jod::hash(scene_name);
    }
}
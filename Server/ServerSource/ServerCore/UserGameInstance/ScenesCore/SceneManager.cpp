/*
 * SceneManager.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "SceneManager.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "Theme0/Scenes/Intro/IntroScene.hpp"
#include "Theme0/Scenes/MainMenu/MainMenuScene.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace JoD {
    SceneManager::SceneManager(
        UserConnection &user_connection) : m_user_connection(user_connection){
        
        AddScene("IntroScene", std::make_shared<IntroScene>(m_user_connection));
        AddScene("MainMenuScene", std::make_shared<MainMenuScene>(m_user_connection));
        AddScene("MainScene", std::make_shared<MainScene>(m_user_connection));
        
        GoTo("IntroScene");
    }
    
    void SceneManager::AddScene(std::string_view sceneName,
                                std::shared_ptr<IScene> scene) {
        scene->Initialize();
        m_scenes.insert({Hash(sceneName), scene});
    }
    
    void SceneManager::UpdateCurrentScene() {
        if (m_scenes.contains(m_current_scene))
            m_scenes.at(m_current_scene)->Update();
    }
    
    void SceneManager::RenderCurrentScene(WebSocket &ws) {
        if (m_scenes.contains(m_current_scene))
            m_scenes.at(m_current_scene)->Render(ws);
    }
    
    void SceneManager::GoTo(std::string_view scene_name) {
        m_current_scene = Hash(scene_name);
    }
}
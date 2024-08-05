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
        UserConnection &userConnection) : m_userConnection(userConnection){
        
        AddScene("IntroScene", std::make_shared<IntroScene>(m_userConnection));
        AddScene(
            "MainMenuScene",
            std::make_shared<MainMenuScene>(m_userConnection));
        AddScene("MainScene", std::make_shared<MainScene>(m_userConnection));
        
        GoTo("IntroScene");
    }
    
    void SceneManager::AddScene(std::string_view sceneName,
                                std::shared_ptr<IScene> scene) {
        scene->Initialize();
        m_scenes.insert({Hash(sceneName), scene});
    }
    
    void SceneManager::UpdateCurrentScene() {
        
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene)->Update();
    }
    
    void SceneManager::RenderCurrentScene(WebSocket &ws) const {
        
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene)->Render(ws);
    }
    
    void SceneManager::GoTo(std::string_view scene_name) {
        
        m_currentScene = Hash(scene_name);
    }
}
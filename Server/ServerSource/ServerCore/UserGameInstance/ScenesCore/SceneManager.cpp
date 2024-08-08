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

namespace JoD {
    
    SceneManager::SceneManager(
        UserGameInstanceEngine &userGameInstanceEngine) : m_userGameInstanceEngine(userGameInstanceEngine){
        
        AddScene("IntroScene", std::make_shared<IntroScene>(m_userGameInstanceEngine));
        
        AddScene(
            "MainMenuScene",
            std::make_shared<MainMenuScene>(m_userGameInstanceEngine));
        
        AddScene("MainScene", std::make_shared<MainScene>(m_userGameInstanceEngine));
        
        GoToScene("IntroScene");
    }
    
    void SceneManager::AddScene(
        std::string_view sceneName,
        std::shared_ptr<IScene> scene) {
        
        scene->Initialize();
        
        m_scenes.insert({Hash(sceneName), scene});
    }
    
    void SceneManager::UpdateCurrentScene() {
        
        if (m_scenes.contains(m_currentScene)) {
            
            m_scenes.at(m_currentScene)->Update();
        }
    }
    
    void SceneManager::RenderCurrentScene(WebSocket &webSocket) const {
        
        if (m_scenes.contains(m_currentScene)) {
            
            m_scenes.at(m_currentScene)->Render(webSocket);
        }
    }
    
    void SceneManager::GoToScene(std::string_view scene_name) {
        
        m_currentScene = Hash(scene_name);
    }
}
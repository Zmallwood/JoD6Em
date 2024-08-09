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
        EngineInstance &engineInstance) : m_engineInstance(engineInstance){
        
        AddScene("IntroScene", std::make_unique<IntroScene>(m_engineInstance));
        
        AddScene(
            "MainMenuScene",
            std::make_unique<MainMenuScene>(m_engineInstance));
        
        AddScene("MainScene", std::make_unique<MainScene>(m_engineInstance));
        
        GoToScene("IntroScene");
    }
    
    void SceneManager::AddScene(
        std::string_view sceneName,
        std::unique_ptr<IScene> scene) {
        
        scene->Initialize();
        
        m_scenes.insert({Hash(sceneName), std::move(scene)});
    }
    
    void SceneManager::UpdateCurrentScene(UserID userID) {
        
        if (m_scenes.contains(m_currentScene)) {
            
            m_scenes.at(m_currentScene)->Update(userID);
        }
    }
    
    void SceneManager::RenderCurrentScene(UserID userID, WebSocket &webSocket) const {
        
        if (m_scenes.contains(m_currentScene)) {
            
            m_scenes.at(m_currentScene)->Render(userID, webSocket);
        }
    }
    
    void SceneManager::GoToScene(std::string_view scene_name) {
        
        m_currentScene = Hash(scene_name);
        
        if (m_scenes.contains(m_currentScene)) {
            
            m_scenes.at(m_currentScene)->OnEnter();
        }
    }
}
/*
 * EngineInstance.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */


#include "EngineInstance.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    
    EngineInstance::EngineInstance()
        : m_sceneManager(std::make_unique<JoD::SceneManager>(*this)),
        m_mouseInput(std::make_unique<JoD::MouseInput>()),
        m_serverFPSCounter(std::make_unique<ServerFPSCounter>()),
        m_player(std::make_unique<JoD::Player>()),
        m_cursor(std::make_unique<Cursor>(*this)){
        
    }
    
    void EngineInstance::Update(UserID userID) {
        
        m_sceneManager->UpdateCurrentScene(userID);
        
        m_serverFPSCounter->Update();
    }
    
    void EngineInstance::Render(UserID userID, WebSocket &webSocket) const {
        
        m_sceneManager->RenderCurrentScene(userID, webSocket);
        
        m_serverFPSCounter->Render(webSocket);
        
        m_cursor->Render(userID, webSocket);
        
        SendPresentCanvasInstruction(webSocket);
    }
    
    float EngineInstance::GetAspectRatio() const {
        
        return static_cast<float>(m_canvasSize.w) / m_canvasSize.h;
    }
}
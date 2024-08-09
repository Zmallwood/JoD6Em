/*
 * EngineInstance.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */


#include "EngineInstance.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerFPSCounter.hpp"
#include "ScenesCore/SceneManager.hpp"
#include "ServerCore/UserGameInstance/Cursor/Cursor.hpp"
#include "TextOutput/TextMessages.hpp"

namespace JoD {
    
    struct EngineInstance::Impl {
        PointF mousePosition; ///< Current mosue position in the browser canvas.
        Size canvasSize; ///< Size of canvas in browser.
        std::unique_ptr<JoD::MouseInput> mouseInput; ///< Handles mouse input and provides state.
        std::unique_ptr<JoD::SceneManager> sceneManager; ///< Manages game scenes for the user s instance.
        std::unique_ptr<JoD::Player> player; ///< Player instance for the user.
        std::unique_ptr<Cursor> cursor; ///< Custom cursor which replaces default system cursor.
        std::unique_ptr<ServerFPSCounter> serverFPSCounter; ///< Server side FPS counter.
        std::unique_ptr<JoD::TextMessages> textMessages;
    };
    
    EngineInstance::EngineInstance()
        : m_pImpl(std::make_unique<Impl>()) {
        
        m_pImpl->sceneManager = std::make_unique<JoD::SceneManager>(*this);
        m_pImpl->mouseInput = std::make_unique<JoD::MouseInput>();
        m_pImpl->serverFPSCounter = std::make_unique<ServerFPSCounter>();
        m_pImpl->player = std::make_unique<JoD::Player>();
        m_pImpl->cursor = std::make_unique<Cursor>();
        m_pImpl->textMessages = std::make_unique<JoD::TextMessages>();
    }
    
    EngineInstance::~EngineInstance() {
        
    }
    
    void EngineInstance::Update(UserID userID) {
        
        m_pImpl->sceneManager->UpdateCurrentScene(userID);
        
        m_pImpl->serverFPSCounter->Update();
    }
    
    void EngineInstance::Render(UserID userID, WebSocket &webSocket) const {
        
        m_pImpl->sceneManager->RenderCurrentScene(userID, webSocket);
        
        m_pImpl->serverFPSCounter->Render(webSocket);
        
        m_pImpl->cursor->Render(userID, webSocket);
        
        SendPresentCanvasInstruction(webSocket);
    }
    
    float EngineInstance::GetAspectRatio() const {
        
        return static_cast<float>(m_pImpl->canvasSize.w) / m_pImpl->canvasSize.h;
    }
    
    PointF EngineInstance::MousePosition() const {
        
        return m_pImpl->mousePosition;
    }
    
    void EngineInstance::SetMousePosition(PointF value) {
        
        m_pImpl->mousePosition = value;
    }
    
    void EngineInstance::SetCanvasSize(Size value) {
        
        m_pImpl->canvasSize = value;
    }
    
    JoD::MouseInput *EngineInstance::MouseInput() const {
        
        return m_pImpl->mouseInput.get();
    }
    
    JoD::SceneManager *EngineInstance::SceneManager() const {
        
        return m_pImpl->sceneManager.get();
    }
    
    JoD::Player *EngineInstance::Player() const {
        
        return m_pImpl->player.get();
    }
    
    JoD::TextMessages *EngineInstance::TextOut() const {
        
        return m_pImpl->textMessages.get();
    }
}
/*
 * EngineInstance.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */


#include "EngineInstance.hpp"
#include "Common/Aliases.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerFPSCounter.hpp"
#include "ScenesCore/SceneManager.hpp"
#include "ServerCore/UserGameInstance/Cursor/Cursor.hpp"
#include "TextOutput/TextMessages.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
    
    struct EngineInstance::Impl {
        
        // Construct the implementation object by passing the users socket object.
        Impl(Socket socket)
            : webSocket(std::move(socket)) {}
        
        PointF mousePosition;                               // Current mosue position in the browser canvas.
        
        Size canvasSize;                                    // Size of canvas in browser.
        
        std::unique_ptr<MouseInput> mouseInput;             // Handles mouse input and provides state.
        
        std::unique_ptr<SceneManager> sceneManager;         // Manages game scenes for the user s instance.
        
        std::unique_ptr<Player> player;                     // Player instance for the user.
        
        std::unique_ptr<Cursor> cursor;                     // Custom cursor which replaces default system cursor.
        
        std::unique_ptr<ServerFPSCounter> serverFPSCounter; // Server side FPS counter.
        
        std::unique_ptr<TextMessages> textMessages;         // Manages printed text messages to the user.
        
        WebSocket webSocket;                                // User for network communication with the user.
    };
    
    EngineInstance::EngineInstance(UserID userID, Socket socket)
        : m_pImpl(std::make_unique<Impl>(std::move(socket))) {
        
        // Create engine component objects.
        
        m_pImpl->sceneManager = std::make_unique<SceneManager>(userID);
        m_pImpl->mouseInput = std::make_unique<MouseInput>();
        m_pImpl->serverFPSCounter = std::make_unique<ServerFPSCounter>();
        m_pImpl->player = std::make_unique<Player>();
        m_pImpl->cursor = std::make_unique<Cursor>();
        m_pImpl->textMessages = std::make_unique<TextMessages>();
    }
    
    EngineInstance::~EngineInstance() {}
    
    void EngineInstance::Reset() {
        
        // Reset cursor type in the beginning of each frame.
        m_pImpl->cursor->ResetCursorType();
    }
    
    void EngineInstance::Update(UserID userID) {
        
        // Update the current scenes logic.
        m_pImpl->sceneManager->UpdateCurrentScene(userID);
        
        // Update he server side FPS counter.
        m_pImpl->serverFPSCounter->Update();
    }
    
    void EngineInstance::Render(UserID userID) const {
        
        // Render the current scene.
        m_pImpl->sceneManager->RenderCurrentScene(userID);
        
        // Render the server side FPS counter.
        m_pImpl->serverFPSCounter->Render(userID);
        
        // Render the mouse cursor.
        m_pImpl->cursor->Render(userID);
        
        // Let user know that canvas rendering is finished,
        // and the canvas can be presented.
        SendPresentCanvasInstruction(userID);
    }
    
    float EngineInstance::GetAspectRatio() const {
        
        // Calculate aspect ratio (width/height) and return.
        return static_cast<float>(m_pImpl->canvasSize.w) /
               m_pImpl->canvasSize.h;
    }
    
    PointF EngineInstance::GetMousePosition() const {
        
        // Return mouse position in canvas.
        return m_pImpl->mousePosition;
    }
    
    void EngineInstance::SetMousePosition(PointF value) {
        
        // Set mouse position in canvas.
        m_pImpl->mousePosition = value;
    }
    
    void EngineInstance::SetCanvasSize(Size value) {
        
        // Set new canvas size in browser.
        m_pImpl->canvasSize = value;
    }
    
    MouseInput *EngineInstance::GetMouseInput() const {
        
        // Return raw pointer to MouseInput object.
        return m_pImpl->mouseInput.get();
    }
    
    SceneManager *EngineInstance::GetSceneManager() const {
        
        // Return raw pointer to SceneManager object.
        return m_pImpl->sceneManager.get();
    }
    
    Player *EngineInstance::GetPlayer() const {
        
        // Return raw pointer to Player object.
        return m_pImpl->player.get();
    }
    
    TextMessages *EngineInstance::GetTextMessages() const {
        
        // Return raw pointer to TextMessages object.
        return m_pImpl->textMessages.get();
    }
    
    WebSocket *EngineInstance::GetWebSocket() const {
        
        // Return raw pointer to WebSocket object.
        return &m_pImpl->webSocket;
    }
    
    
    Cursor *EngineInstance::GetCursor() const {
        
        // Return raw pointer to Cursor object.
        return m_pImpl->cursor.get();
    }
}
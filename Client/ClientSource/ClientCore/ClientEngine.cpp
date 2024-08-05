/*
 * ClientEngine.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ClientEngine.hpp"
#include "ClientCore/Graphics/Graphics.hpp"
#include "MessageCodes.hpp"
#include "ClientCore/Net/WebSocketServerConnection.hpp"
#include "Instructions/RenderInstructionsManager.hpp"
#include "Input/SetupInputCallbacks.hpp"
#include "Utilities/ClientFPSCounter.hpp"

namespace JoD {
    
    namespace {
        
        void GameLoopFunction();
    }
    
    void ClientEngine::Run() const {
        
        // Start network connection.
        _<WebSocketServerConnection>().Connect();
        
        // Required by SDL2 before using it.
        SDL_Init(SDL_INIT_EVERYTHING);
        
        SetupInputCallbacks();
        
        // Touch Graphics to initialize it.
        _<Graphics>();
        
        // Start game loop.
        auto simulateInfiniteLoop = 1;
        emscripten_set_main_loop(GameLoopFunction, 0, simulateInfiniteLoop);
    }
    
    void ClientEngine::PollEvents() {
        
        SDL_Event event;
        
        // Poll for events from user every frame.
        while (SDL_PollEvent(&event)) {
            
            switch (event.type){
            
            case SDL_QUIT: {
                
                // Quit game by stopping ClientEngine.
                m_running = false;
                
                break;
            }
            }
        }
    }
    
    namespace {
        
        void GameLoopFunction() {
            
            // Exit main loop if user has requested it.
            if (!_<ClientEngine>().m_running) {
                
                emscripten_cancel_main_loop();
            }
            
            // Poll user events and process them.
            _<ClientEngine>().PollEvents();
            
            _<ClientFPSCounter>().Update();
            
            _<WebSocketServerConnection>().SendMessage(
                MessageCodes::k_mousePosition);
            
            // Clear canvas with single color to prepare for new rendering.
            _<Graphics>().ClearCanvas();
            
            // Draw canvas in its current state (current set of drawing instructions).
            _<RenderInstrutionsManager>().ExecuteInstructions();
            
            _<ClientFPSCounter>().Render();
            
            // Present canvas to users web browser.
            _<Graphics>().PresentCanvas();
            
            _<WebSocketServerConnection>().SendMessage(
                MessageCodes::k_frameFinished);
        }
    }
}
/*
 * ClientEngine.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ClientEngine.hpp"
#include "ClientCore/Graphics/Graphics.hpp"
#include "MessageCodes.hpp"
#include "ClientCore/Net/WebSocketServerConnection.hpp"
#include "DrawInstructions/DrawInstructionsManager.hpp"
#include "Input/SetupInputCallbacks.hpp"
#include "Utilities/ClientFPSCounter.hpp"

namespace JoD {
    
    namespace {
        
        // Called infinitely in the emscripten game loop.
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
        const auto simulateInfiniteLoop = 1;
        emscripten_set_main_loop(GameLoopFunction, 0, simulateInfiniteLoop);
    }
    
    namespace {
        
        void GameLoopFunction() {
            
            // Exit main loop if user has requested it.
            if (!_<ClientEngine>().GetRunning()) {
                
                emscripten_cancel_main_loop();
            }
            
            // Update client side FPS counter.
            _<ClientFPSCounter>().Update();
            
            // Send net message with mouse position each frame.
            _<WebSocketServerConnection>().SendMessage(
                MessageCodes::k_mousePosition);
            
            // Clear canvas with single color to prepare for new rendering.
            _<Graphics>().ClearCanvas();
            
            // Draw canvas in its current state (current set of drawing instructions).
            _<DrawInstructionsManager>().ExecuteInstructions();
            
            // Draw the FPS text on top of everything else.
            _<ClientFPSCounter>().Render();
            
            // Present canvas to users web browser.
            _<Graphics>().PresentCanvas();
        }
    }
}
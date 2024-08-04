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
        _<WebSocketServerConnection>().Connect(); // Start network connection.
        SDL_Init(SDL_INIT_EVERYTHING); // Required by SDL2 before using it.
        SetupInputCallbacks();
        _<Graphics>(); // Touch Graphics to initialize it.
        // Start game loop.
        auto simulate_infinite_loop = 1;
        emscripten_set_main_loop(GameLoopFunction, 0, simulate_infinite_loop);
    }
    
    void ClientEngine::PollEvents()      {
        SDL_Event event;
        while (SDL_PollEvent(
                   &event)) { // Poll for events from user every frame.
            switch (event.type){
            case SDL_QUIT: {
                m_running = false; // Quit game by stopping ClientEngine.
                break;
            }
            }
        }
    }
    
    namespace {
        void GameLoopFunction() {
            if (!_<ClientEngine>().m_running) // Exit main loop if user has requested it.
                emscripten_cancel_main_loop();
            _<ClientEngine>().PollEvents(); // Poll user events and process them.
            _<ClientFPSCounter>().Update();
            _<WebSocketServerConnection>().SendMessage(
                MessageCodes::k_mouse_position);
            // Clear canvas with single color to prepare for new rendering.
            _<Graphics>().ClearCanvas();
            // Draw canvas in its current state (current set of drawing instructions).
            _<RenderInstrutionsManager>().ExecuteInstructions();
            _<ClientFPSCounter>().Render();
            _<Graphics>().PresentCanvas(); // Present canvas to users web browser.
            _<WebSocketServerConnection>().SendMessage(
                MessageCodes::k_frame_finished);
        }
    }
}
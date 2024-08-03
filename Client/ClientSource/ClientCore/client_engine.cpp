/*
 * client_engine.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "client_engine.h"
#include "ClientCore/Graphics/graphics.h"
#include "message_codes.h"
#include "ClientCore/Net/web_socket_server_connection.h"
#include "Instructions/render_instructions_manager.h"
#include "Input/setup_callbacks.h"
#include "Utilities/fps_counter.h"

namespace jod {
    namespace {
        void game_loop_function();
    }
    
    void client_engine::run() const {
        _<web_socket_server_connection>().connect(); // Start network connection.
        SDL_Init(SDL_INIT_EVERYTHING); // Required by SDL2 before using it.
        setup_callbacks();
        _<graphics>(); // Touch Graphics to initialize it.
        // Start game loop.
        auto simulate_infinite_loop = 1;
        emscripten_set_main_loop(game_loop_function, 0, simulate_infinite_loop);
    }
    
    void client_engine::poll_events()      {
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
        void game_loop_function()      {
            if (!_<client_engine>().m_running) // Exit main loop if user has requested it.
                emscripten_cancel_main_loop();
            _<client_engine>().poll_events(); // Poll user events and process them.
            _<fps_counter>().update();
            _<web_socket_server_connection>().send_message(
                message_codes::k_mouse_position);
            // Clear canvas with single color to prepare for new rendering.
            _<graphics>().clear_canvas();
            // Draw canvas in its current state (current set of drawing instructions).
            _<render_instructions_manager>().execute_instructions();
            _<fps_counter>().render();
            _<graphics>().present_canvas(); // Present canvas to users web browser.
            _<web_socket_server_connection>().send_message(
                message_codes::k_frame_finished);
        }
    }
}
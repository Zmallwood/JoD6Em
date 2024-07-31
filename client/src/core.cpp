// Copyright (c) 2024 Andreas Åkerberg.
#include "core.h"
#include "graphics.h"
#include "message_codes.h"
#include "net.h"
#include "rendering.h"
namespace jod {
    namespace {
        void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
        void character_callback(GLFWwindow *window, unsigned int codepoint);
        EM_BOOL touch_start_callback(int, EmscriptenTouchEvent const *, void *);
        EM_BOOL touch_end_callback(int, EmscriptenTouchEvent const *, void *);
        void game_loop_function();
    }
    void
    run_new_client_instance(){
        _<client_engine>().run(); // Access ClientEngine and run it.
    }
    void
    client_engine::run() const {
        _<web_socket_server_connection>().connect(); // Start network connection.
        SDL_Init(SDL_INIT_EVERYTHING); // Required by SDL2 before using it.
        _<input_manager>();
        _<graphics>(); // Touch Graphics to initialize it.
        // Start game loop.
        auto simulateInfiniteLoop = 1;
        emscripten_set_main_loop(game_loop_function, 0, simulateInfiniteLoop);
    }
    void
    client_engine::poll_events(){
        SDL_Event event;
        while (SDL_PollEvent(&event)) { // Poll for events from user every frame.
            switch (event.type){
            case SDL_QUIT: {
                m_running = false; // Quit game by stopping ClientEngine.
                break;
            }
            }
        }
    }
    input_manager::input_manager(){
        // Set callback for keyboard events.
        glfwSetKeyCallback(_<graphics>().m_window, key_callback);
        // Set callback for mouse events.
        glfwSetMouseButtonCallback(_<graphics>().m_window, mouse_button_callback);
        // Set callback for text typing events.
        glfwSetCharCallback(_<graphics>().m_window, character_callback);
        // Set callback for touch start event.
        emscripten_set_touchstart_callback("#canvas", nullptr, true, touch_start_callback);
        // Set callback for touch end event.
        emscripten_set_touchend_callback("#canvas", nullptr, true, touch_end_callback);
    }
    render_instructions_manager::render_instructions_manager(){
        // Create a sufficient amount of RIDs for drawing images and game start.
        for (auto i = 0; i < k_maxNumDrawInstructions; i++)
            m_rids.push_back(_<image_renderer>().new_image());
    }
    void
    render_instructions_manager::add_image_draw_instruction(int imageNameHash, RectF dest){
        // Create a new image draw instruction and save it.
        auto newInstruction = image_draw_instruction{m_rids.at(m_imageDrawInstructionsBuffer.size()),
                                                     imageNameHash, dest};
        m_imageDrawInstructionsBuffer.push_back(newInstruction);
    }
    void
    render_instructions_manager::apply_buffer(){
        // Replace the current instruction group with the new one.
        m_imageDrawInstructions = m_imageDrawInstructionsBuffer;
        // Prepare the next-instructions-set for storing a new set
        // of instructions by clearing it.
        m_imageDrawInstructionsBuffer.clear();
    }
    void
    render_instructions_manager::execute_instructions(){
        // Execute all drawing instructions that have been added.
        for (auto &instr : m_imageDrawInstructions)
            _<image_renderer>().draw_image(instr.rid, instr.imageNameHash, instr.dest);
    }
    namespace {
        void
        game_loop_function(){
            if (!_<client_engine>().m_running) // Exit main loop if user has requested it.
                emscripten_cancel_main_loop();
            _<client_engine>().poll_events(); // Poll user events and process them.
            _<web_socket_server_connection>().send_message(message_codes::k_mousePosition);
            // Clear canvas with single color to prepare for new rendering.
            _<graphics>().clear_canvas();
            // Draw canvas in its current state (current set of drawing instructions).
            _<render_instructions_manager>().execute_instructions();
            _<graphics>().present_canvas(); // Present canvas to users web browser.
            _<web_socket_server_connection>().send_message(message_codes::k_frameFinished);
        }
        void
        key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
            // if (action == GLFW_PRESS)
            //     _<KeyboardInput>().OnKeyPress(key);
            // else if (action == GLFW_RELEASE)
            //     _<KeyboardInput>().OnKeyRelease(key);
        }
        void
        mouse_button_callback(GLFWwindow *window, int button, int action, int mods){
            static bool mouseDown = false;
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !mouseDown){
                _<web_socket_server_connection>().send_message(message_codes::k_mouseDown);
                mouseDown = true;
            } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
                mouseDown = false;
            }
            // if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            //     _<MouseInput>().LeftButton().OnPress();
            // else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
            //     _<MouseInput>().LeftButton().OnRelease();
            // else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
            //     _<MouseInput>().RightButton().OnPress();
            // else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
            //     _<MouseInput>().RightButton().OnRelease();
        }
        void
        character_callback(GLFWwindow *window, unsigned int codepoint){
            // _<KeyboardInput>().AppendTextInput(std::string(1, (char)codepoint));
        }
        EM_BOOL
        touch_start_callback(int, EmscriptenTouchEvent const *, void *){
            // _<MouseInput>().LeftButton().OnPress();
            return EM_FALSE;
        }
        EM_BOOL
        touch_end_callback(int, EmscriptenTouchEvent const *, void *){
            // _<MouseInput>().LeftButton().OnRelease();
            return EM_FALSE;
        }
    }
}
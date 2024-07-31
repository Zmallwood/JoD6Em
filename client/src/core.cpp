// Copyright (c) 2024 Andreas Åkerberg.
#include "core.h"
#include "graphics.h"
#include "message_codes.h"
#include "net.h"
#include "rendering.h"
namespace jod {
    namespace {
        void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
        void CharacterCallback(GLFWwindow *window, unsigned int codepoint);
        EM_BOOL TouchStartCallback(int, EmscriptenTouchEvent const *, void *);
        EM_BOOL TouchEndCallback(int, EmscriptenTouchEvent const *, void *);
        void GameLoopFunction();
    }
    void
    RunNewClientInstance(){
        _<ClientEngine>().Run(); // Access ClientEngine and run it.
    }
    void
    ClientEngine::Run() const {
        _<WebSocketServerConnection>().Connect(); // Start network connection.
        SDL_Init(SDL_INIT_EVERYTHING); // Required by SDL2 before using it.
        _<InputManager>();
        _<Graphics>(); // Touch Graphics to initialize it.
        // Start game loop.
        auto simulateInfiniteLoop = 1;
        emscripten_set_main_loop(GameLoopFunction, 0, simulateInfiniteLoop);
    }
    void
    ClientEngine::PollEvents(){
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
    InputManager::InputManager(){
        // Set callback for keyboard events.
        glfwSetKeyCallback(_<Graphics>().m_window, KeyCallback);
        // Set callback for mouse events.
        glfwSetMouseButtonCallback(_<Graphics>().m_window, MouseButtonCallback);
        // Set callback for text typing events.
        glfwSetCharCallback(_<Graphics>().m_window, CharacterCallback);
        // Set callback for touch start event.
        emscripten_set_touchstart_callback("#canvas", nullptr, true, TouchStartCallback);
        // Set callback for touch end event.
        emscripten_set_touchend_callback("#canvas", nullptr, true, TouchEndCallback);
    }
    RenderInstructionsManager::RenderInstructionsManager(){
        // Create a sufficient amount of RIDs for drawing images and game start.
        for (auto i = 0; i < k_maxNumDrawInstructions; i++)
            m_rids.push_back(_<ImageRenderer>().NewImage());
    }
    void
    RenderInstructionsManager::AddImageDrawInstruction(int imageNameHash, RectF dest){
        // Create a new image draw instruction and save it.
        auto newInstruction = ImageDrawInstruction{m_rids.at(m_imageDrawInstructionsBuffer.size()),
                                                   imageNameHash, dest};
        m_imageDrawInstructionsBuffer.push_back(newInstruction);
    }
    void
    RenderInstructionsManager::ApplyBuffer(){
        // Replace the current instruction group with the new one.
        m_imageDrawInstructions = m_imageDrawInstructionsBuffer;
        // Prepare the next-instructions-set for storing a new set
        // of instructions by clearing it.
        m_imageDrawInstructionsBuffer.clear();
    }
    void
    RenderInstructionsManager::ExecuteInstructions(){
        // Execute all drawing instructions that have been added.
        for (auto &instr : m_imageDrawInstructions)
            _<ImageRenderer>().DrawImage(instr.rid, instr.imageNameHash, instr.dest);
    }
    namespace {
        void
        GameLoopFunction(){
            if (!_<ClientEngine>().m_running) // Exit main loop if user has requested it.
                emscripten_cancel_main_loop();
            _<ClientEngine>().PollEvents(); // Poll user events and process them.
            _<WebSocketServerConnection>().SendMessage(MessageCodes::k_mousePosition);
            // Clear canvas with single color to prepare for new rendering.
            _<Graphics>().ClearCanvas();
            // Draw canvas in its current state (current set of drawing instructions).
            _<RenderInstructionsManager>().ExecuteInstructions();
            _<Graphics>().PresentCanvas(); // Present canvas to users web browser.
            _<WebSocketServerConnection>().SendMessage(MessageCodes::k_frameFinished);
        }
        void
        KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
            // if (action == GLFW_PRESS)
            //     _<KeyboardInput>().OnKeyPress(key);
            // else if (action == GLFW_RELEASE)
            //     _<KeyboardInput>().OnKeyRelease(key);
        }
        void
        MouseButtonCallback(GLFWwindow *window, int button, int action, int mods){
            static bool mouseDown = false;
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !mouseDown){
                _<WebSocketServerConnection>().SendMessage(MessageCodes::k_mouseDown);
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
        CharacterCallback(GLFWwindow *window, unsigned int codepoint){
            // _<KeyboardInput>().AppendTextInput(std::string(1, (char)codepoint));
        }
        EM_BOOL
        TouchStartCallback(int, EmscriptenTouchEvent const *, void *){
            // _<MouseInput>().LeftButton().OnPress();
            return EM_FALSE;
        }
        EM_BOOL
        TouchEndCallback(int, EmscriptenTouchEvent const *, void *){
            // _<MouseInput>().LeftButton().OnRelease();
            return EM_FALSE;
        }
    }
}
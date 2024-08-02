// setup_callbacks.cpp
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
//

#include "setup_callbacks.h"
#include "client_core/graphics/graphics.h"
#include "client_core/net/web_socket_server_connection.h"
#include "message_codes.h"

namespace jod {
    namespace {
        void key_callback(
            GLFWwindow *window, int key, int scancode, int action, int mods);
        void mouse_button_callback(
            GLFWwindow *window, int button, int action,
            int mods);
        void character_callback(GLFWwindow *window, unsigned int codepoint);
        EM_BOOL touch_start_callback(int, EmscriptenTouchEvent const *, void *);
        EM_BOOL touch_end_callback(int, EmscriptenTouchEvent const *, void *);
    }
    
    void
    setup_callbacks() {
        // Set callback for keyboard events.
        glfwSetKeyCallback(_<graphics>().m_window, key_callback);
        // Set callback for mouse events.
        glfwSetMouseButtonCallback(
            _<graphics>().m_window,
            mouse_button_callback);
        // Set callback for text typing events.
        glfwSetCharCallback(_<graphics>().m_window, character_callback);
        // Set callback for touch start event.
        emscripten_set_touchstart_callback(
            "#canvas",
            nullptr,
            true,
            touch_start_callback);
        // Set callback for touch end event.
        emscripten_set_touchend_callback(
            "#canvas",
            nullptr,
            true,
            touch_end_callback);
    }
    
    namespace {
        void
        key_callback(GLFWwindow *window, int key, int scancode, int action,
                     int mods) {
            // if (action == GLFW_PRESS)
            //     _<KeyboardInput>().OnKeyPress(key);
            // else if (action == GLFW_RELEASE)
            //     _<KeyboardInput>().OnKeyRelease(key);
        }
        
        void
        mouse_button_callback(GLFWwindow *window, int button, int action,
                              int mods) {
            static bool mouseDown = false;
            if (button == GLFW_MOUSE_BUTTON_LEFT
                && action == GLFW_PRESS
                && !mouseDown){
                _<web_socket_server_connection>().send_message(
                    message_codes::k_mouseDown);
                mouseDown = true;
            } else if (button == GLFW_MOUSE_BUTTON_LEFT &&
                       action == GLFW_RELEASE) {
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
        character_callback(
            GLFWwindow *window,
            unsigned int codepoint) {
            // _<KeyboardInput>().AppendTextInput(std::string(1, (char)codepoint));
        }
        
        EM_BOOL
        touch_start_callback(int, EmscriptenTouchEvent const *, void *) {
            // _<MouseInput>().LeftButton().OnPress();
            return EM_FALSE;
        }
        
        EM_BOOL
        touch_end_callback(int, EmscriptenTouchEvent const *, void *) {
            // _<MouseInput>().LeftButton().OnRelease();
            return EM_FALSE;
        }
    }
}
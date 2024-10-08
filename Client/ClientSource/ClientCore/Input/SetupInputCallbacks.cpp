/*
 * SetupCallbacks.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "SetupInputCallbacks.hpp"
#include "ClientCore/Graphics/Graphics.hpp"
#include "ClientCore/Net/WSServerConnection.hpp"
#include "MessageCodes.hpp"

namespace JoD {
namespace {
// Callback function for key events.
    void KeyCallback(
        GLFWwindow *window, int key, int scan_code,
        int action,
        int mods);
// Callback function for mouse button events.
    void MouseButtonCallback(
        GLFWwindow *window, int button, int action,
        int mods);
// Callback function for character typing events.
    void CharacterCallback(
        GLFWwindow *window, unsigned int code_point);
// Callback function for touch start events.
    EM_BOOL TouchStartCallback(
        int, EmscriptenTouchEvent const *, void *);
// Callback function for touch end events.
    EM_BOOL TouchEndCallback(
        int, EmscriptenTouchEvent const *, void *);
}

void SetupInputCallbacks() {
// Set callback for keyboard events.
    glfwSetKeyCallback(_<Graphics>().GetWindow(), KeyCallback);
// Set callback for mouse events.
    glfwSetMouseButtonCallback(
        _<Graphics>().GetWindow(),
        MouseButtonCallback);
// Set callback for text typing events.
    glfwSetCharCallback(_<Graphics>().GetWindow(), CharacterCallback);
// Set callback for touch start event.
    emscripten_set_touchstart_callback(
        "#canvas",
        nullptr,
        true,
        TouchStartCallback);
// Set callback for touch end event.
    emscripten_set_touchend_callback(
        "#canvas",
        nullptr,
        true,
        TouchEndCallback);
}

namespace {
    void KeyCallback(
        GLFWwindow *window, int key, int scanCode,
        int action,
        int mods) {
        // if (action == GLFW_PRESS)
        //     _<KeyboardInput>().OnKeyPress(key);
        // else if (action == GLFW_RELEASE)
        //     _<KeyboardInput>().OnKeyRelease(key);
    }
    
    void MouseButtonCallback(
        GLFWwindow *window, int button, int action,
        int mods) {
        auto & srvConn = _<WSServerConnection>();
// Left mouse button has been pressed.
        if (button == GLFW_MOUSE_BUTTON_LEFT
            && action == GLFW_PRESS){
// Send message to server.
            srvConn.SendMessage(MessageCodes::k_leftMouseDown);
        }
// Left mouse button has been released.
        else if (button == GLFW_MOUSE_BUTTON_LEFT &&
                 action == GLFW_RELEASE) {
// Send message to server.
            srvConn.SendMessage(MessageCodes::k_leftMouseUp);
        }
// Right mouse button has been pressed.
        else if (button == GLFW_MOUSE_BUTTON_RIGHT
                 && action == GLFW_PRESS){
// Send message to server.
            srvConn.SendMessage(MessageCodes::k_rightMouseDown);
        }
// Right mouse button has been released.
        else if (button == GLFW_MOUSE_BUTTON_RIGHT &&
                 action == GLFW_RELEASE) {
// Send message to server.
            srvConn.SendMessage(MessageCodes::k_rightMouseUp);
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
    
    void CharacterCallback(
        GLFWwindow *window,
        unsigned int codePoint) {
        // _<KeyboardInput>().AppendTextInput(std::string(1, (char)code_point));
        auto & srvConn = _<WSServerConnection>();
        int data[2];
        data[0] = MessageCodes::k_textInput;
        data[1] = (int)codePoint;
        srvConn.SendMessage(data, 2);
    }
    
    EM_BOOL TouchStartCallback(
        int, EmscriptenTouchEvent const *,
        void *) {
        // _<MouseInput>().LeftButton().OnPress();
        return EM_FALSE;
    }
    
    EM_BOOL TouchEndCallback(
        int, EmscriptenTouchEvent const *,
        void *) {
        // _<MouseInput>().LeftButton().OnRelease();
        return EM_FALSE;
    }
}
}

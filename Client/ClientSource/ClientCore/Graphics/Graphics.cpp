/*
 * Graphics.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Graphics.hpp"

namespace JoD {
namespace {
    EM_JS(int, CanvasGetWidth, (), { return window.innerWidth; });
    EM_JS(int, CanvasGetHeight, (), { return window.innerHeight; });
}

Graphics::Graphics() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    m_window = glfwCreateWindow(
        CanvasGetWidth(),
        CanvasGetHeight(),
        k_title.c_str(),
        NULL,
        NULL);
    glfwMakeContextCurrent(m_window);
    glEnable( GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Graphics::~Graphics() {
    glfwDestroyWindow(m_window);
}

void Graphics::ClearCanvas() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::PresentCanvas() const {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
    glFinish();
}
}

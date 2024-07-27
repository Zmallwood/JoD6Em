#include "Graphics.h"
#include "Rendering.h"

namespace jod
{
    EM_JS(int, CanvasGetWidth, (), { return window.innerWidth; });
    EM_JS(int, CanvasGetHeight, (), { return window.innerHeight; });

    Graphics::Graphics()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        m_window = glfwCreateWindow(CanvasGetWidth(), CanvasGetHeight(), k_title.c_str(), NULL, NULL);
        glfwMakeContextCurrent(m_window);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Graphics::ClearCanvas()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Graphics::PresentCanvas()
    {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
        glFinish();
    }
}
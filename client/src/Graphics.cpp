// Copyright (c) 2024 Andreas Åkerberg.

#include "Graphics.h"

#include "Rendering.h"

namespace jod
{
    /* Use javascript call to get browser-canvas width. */
    EM_JS(int, CanvasGetWidth, (), { return window.innerWidth; });

    /* Use javascript call to get browser-canvas height. */
    EM_JS(int, CanvasGetHeight, (), { return window.innerHeight; });

    Graphics::Graphics()
    {
        /* Initialize GLFW. */
        glfwInit();

        /* Use OPENGL ES, which is used for browser OpenGL. */
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

        /* Set OpenGL version. */
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        /* Create GLFW window object. */
        m_window =
            glfwCreateWindow(CanvasGetWidth(), CanvasGetHeight(), k_title.c_str(), NULL, NULL);

        /* Activate current window. */
        glfwMakeContextCurrent(m_window);

        /* Enable alpha blending to allow transparency in rendering. */
        glEnable(GL_BLEND);

        /* Set desired alpha blending functions. */
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Graphics::ClearCanvas()
    {
        /* Clear canvas to prepare for rendering new contents. */
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Graphics::PresentCanvas()
    {
        /* Present buffer to web browser. */
        glfwSwapBuffers(m_window);

        /* Poll new input events from user. */
        glfwPollEvents();

        /* Do not return until previously issued commands have finished. */
        glFinish();
    }

    Cursor::Cursor()
    {
        glfwSetInputMode(_<Graphics>().m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        m_ridCursorImage = _<ImageRenderer>().NewImage();
    }

    void Cursor::Render() const
    {
        auto mousePos = GetMousePosition();

        auto cursorWidth = k_cursorSize;
        auto cursorHeight = ConvertWidthToHeight(k_cursorSize);

        auto cursorX = mousePos.x - cursorWidth / 2;
        auto cursorY = mousePos.y - cursorHeight / 2;

        auto cursorArea = RectF{cursorX, cursorY, cursorWidth, cursorHeight};
        
        _<ImageRenderer>().DrawImage(m_ridCursorImage, k_cursorImageName, cursorArea);
    }
}
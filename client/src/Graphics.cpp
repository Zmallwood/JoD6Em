// Copyright (c) 2024 Andreas Åkerberg.

#include "Graphics.h"

#include "Rendering.h"

namespace jod {
    // Use javascript call to get browser-canvas width.
    EM_JS(int, CanvasGetWidth, (), { return window.innerWidth; });
    // Use javascript call to get browser-canvas height.
    EM_JS(int, CanvasGetHeight, (), { return window.innerHeight; });
    
    Graphics::Graphics(){
        glfwInit(); // Initialize GLFW.
        // Use OPENGL ES, which is used for browser OpenGL.
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        // Set OpenGL version.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        // Create GLFW window object.
        m_window = glfwCreateWindow(CanvasGetWidth(), CanvasGetHeight(), k_title.c_str(), NULL, NULL);
        glfwMakeContextCurrent(m_window); // Activate current window.
        glEnable(GL_BLEND); // Enable alpha blending to allow transparency in rendering.
        // Set desired alpha blending functions.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    void Graphics::ClearCanvas(){
        glClear(GL_COLOR_BUFFER_BIT); // Clear canvas to prepare for rendering new contents.
    }
    
    void Graphics::PresentCanvas(){
        glfwSwapBuffers(m_window); // Present buffer to web browser.
        glfwPollEvents(); // Poll new input events from user.
        // Do not return until previously issued commands have finished.
        glFinish();
    }
    
    Cursor::Cursor(){
        // Hide default system cursor.
        glfwSetInputMode(_<Graphics>().m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        // Allocate image resource for cursor image.
        m_ridCursorImage = _<ImageRenderer>().NewImage();
    }
    
    void Cursor::Render() const {
        auto mousePos = GetMousePosition(); // Get current mouse position.
        // Obtain cursor dimensions.
        auto cursorWidth = k_cursorSize;
        auto cursorHeight = ConvertWidthToHeight(k_cursorSize);
        // Calculate cursor position.
        auto cursorX = mousePos.x - cursorWidth / 2;
        auto cursorY = mousePos.y - cursorHeight / 2;
        // Create render destination rectangle.
        auto cursorDest = RectF{cursorX, cursorY, cursorWidth, cursorHeight};
        // Render the cursor image.
        _<ImageRenderer>().DrawImage(m_ridCursorImage, k_cursorImageName, cursorDest);
    }
}
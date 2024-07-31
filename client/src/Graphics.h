// Copyright (c) 2024 Andreas Åkerberg.
#pragma once

namespace jod {
    /////////////////////////////////////////////////
    /// \brief Initializes and handles preparing and finilizing graphics for each frame.
    /////////////////////////////////////////////////
    class Graphics {
    public:
        /////////////////////////////////////////////////
        /// \brief Construct a new Graphics object and initialize GLFW with OpenGL and applying
        ///        needed settings.
        /////////////////////////////////////////////////
        Graphics();
        /////////////////////////////////////////////////
        /// \brief Clear web browser before rendering new contents.
        /////////////////////////////////////////////////
        void ClearCanvas();
        /////////////////////////////////////////////////
        /// \brief Present all rendered contents stored in the buffer.
        /////////////////////////////////////////////////
        void PresentCanvas();
        
        GLFWwindow *m_window = nullptr; ///< GLFW window object.
    private:
        const std::string k_title = "Journey of Dreams"; ///< Window title used if the game would be in desktop application format.
    };
    
    /////////////////////////////////////////////////
    /// \brief Custom cursor object which replaces the default system cursor.
    /////////////////////////////////////////////////
    class Cursor {
    public:
        /////////////////////////////////////////////////
        /// \brief Construct a new Cursor object by hiding the default system cursor and allocate
        ///        resources for drawing cursor images.
        /////////////////////////////////////////////////
        Cursor();
        /////////////////////////////////////////////////
        /// \brief Render the cursor to web browser.
        /////////////////////////////////////////////////
        void Render() const;
    private:
        RID m_ridCursorImage; ///< Resource ID for cursor image.
        const std::string k_cursorImageName = "CursorDefault"; ///< Image name for default cursor style.
        const float k_cursorSize = 0.03f; ///< Size of rendered cursor symbol.
    };
}
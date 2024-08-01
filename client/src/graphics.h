// graphics.h
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
///////////////////////////////////////////////////////////

#pragma once

namespace jod {
    //! \brief Initializes and handles preparing and finilizing graphics for each frame.
    class graphics {
    public:
        //! \brief Construct a new Graphics object and initialize GLFW with OpenGL and applying
        //!        needed settings.
        graphics();
        
        //! \brief Clear web browser before rendering new contents.
        void clear_canvas();
        
        //! \brief Present all rendered contents stored in the buffer.
        void present_canvas();
        
        GLFWwindow *m_window = nullptr; //!< GLFW window object.
        
    private:
        const std::string
            k_title = "Journey of Dreams"; //!< Window title used if the game would be in desktop application format.
    };
}
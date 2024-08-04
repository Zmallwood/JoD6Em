/*
 * Graphics.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    /// @brief Initializes and handles preparing and finilizing graphics for each frame.
    class Graphics {
    public:
        /// @brief Construct a new Graphics object and initialize GLFW with OpenGL and applying
        ///        needed settings.
        Graphics();
        
        /// @brief Clear web browser before rendering new contents.
        void ClearCanvas() const;
        
        /// @brief Present all rendered contents stored in the buffer.
        void PresentCanvas() const;
        
        GLFWwindow *m_window = nullptr; ///< GLFW window object.
        
    private:
        const std::string
            k_title = "Journey of Dreams"; ///< Window title used if the game would be in desktop application format.
    };
}
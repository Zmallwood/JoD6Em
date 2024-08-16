/*
 * Graphics.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

    ///
    /// Initializes and handles preparing and finilizing graphics for each frame.
    ///
    class Graphics {

      public:
        ///
        /// Construct a new Graphics object and initialize GLFW with OpenGL and applying
        /// needed settings.
        ///
        Graphics();

        ///
        /// Destroy the Graphics object, probably not relevant for emscripten app but including
        /// it for the case if the game would be ported into another format.
        ///
        ~Graphics();

        ///
        /// Clear web browser before rendering new contents.
        ///
        void ClearCanvas() const;

        ///
        /// Present all rendered contents stored in the buffer.
        ///
        void PresentCanvas() const;

        ///
        /// Get the GLFW window object which enables rendering using OpenGL to the browser window.
        ///
        /// @return GLFWwindow* GLFW window object.
        ///
        GLFWwindow *GetWindow() const {

            return m_window;
        }

      private:

        // Members

        GLFWwindow *m_window {nullptr}; ///< GLFW window object.

        const std::string k_title       ///< Window title used if the game would be in desktop application format.
        {"Journey of Dreams"};
    };
}

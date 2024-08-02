/*
 * shader_program.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    //! \brief OpenGL shader program object.
    class shader_program {
    public:
        bool create(
            const GLchar *vertexShaderSource,
            const GLchar *fragmentShaderSource);
        void cleanup();
        
        GLuint m_programID = 0;
        
    private:
        GLuint compile_shader(
            const GLchar *shaderSource,
            GLuint *shader,
            GLenum shaderType);
    };
}
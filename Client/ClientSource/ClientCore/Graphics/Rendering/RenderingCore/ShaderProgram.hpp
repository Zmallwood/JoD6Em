/*
 * ShaderProgram.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    /// OpenGL shader program object.
    class ShaderProgram {
      public:
        /// Create a new shader program with provided
        /// source for vertex and fragment shader.
        /// @param vertexShaderSource Vertex shader source.
        /// @param fragmentShaderSource Fragment shader source.
        /// @return bool True if successful, otherwise false.
        bool Create(const GLchar *vertexShaderSource,
                    const GLchar *fragmentShaderSource);
        
        /// Cleans up allocated resources for this shader program.
        void Cleanup() const;
        
        GLuint m_programID = 0; ///< Shader program ID.
        
      private:
        GLuint CompileShader(const GLchar *shaderSource, GLuint *shader,
                             GLenum shaderType) const;
    };
}
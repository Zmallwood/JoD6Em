/*
 * ShaderProgram.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// OpenGL shader program object.
///
class ShaderProgram {
    
  public:
    ///
    /// Create a new shader program with provided
    /// source for vertex and fragment shader.
    ///
    /// @param vertexShaderSource Vertex shader source.
    /// @param fragmentShaderSource Fragment shader source.
    /// @return bool True if successful, otherwise false.
    ///
    bool Create(
        const GLchar *vertexShaderSource,
        const GLchar *fragmentShaderSource);
    
    ///
    /// Cleans up allocated resources for this shader program.
    ///
    void Cleanup() const;
    
    ///
    /// Get the program ID for the program.
    ///
    /// @return GLuint Program ID.
    ///
    GLuint GetProgramID() const {
        
        return m_programID;
    }
    
  private:
    ///
    /// Compiles provided shader source of specified type and outputs the compiled shared object.
    ///
    /// @param shaderSource Source for shader to compile.
    /// @param out_shader Resulting compiled shader is stored to this.
    /// @param shaderType Type of shader, vertex or fragment.
    /// @return GLuint Success code.
    ///
    GLuint CompileShader(
        const GLchar *shaderSource, GLuint *out_shader,
        GLenum shaderType) const;
    
    // Members
    
    GLuint m_programID {0};     ///< Shader program ID.
};

}

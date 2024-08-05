/*
 * ShaderProgram.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ShaderProgram.hpp"

namespace JoD {
    
    bool ShaderProgram::Create(
        const GLchar *vertexShaderSource,
        const GLchar *fragmentShaderSource){
        
        // To hold the shader IDs.
        GLuint vertexShader = 0;
        GLuint fragmentShader = 0;
        m_programID = glCreateProgram(); // Create GL program.
        auto success = true;
        {
            // Compile vertex shader.
            auto vertexShaderRes = CompileShader(
                vertexShaderSource,
                &vertexShader,
                GL_VERTEX_SHADER);
            if (vertexShaderRes != GL_TRUE){ // Check for errors.
                std::cout << "Unable to compile vertex shader.\n";
                success = false;
            }
        }
        // If previous steps were successful, continue.
        if (success){
            // Attach compiled vertex shader to GL program.
            glAttachShader(m_programID, vertexShader);
            // Compile fragment shader.
            auto fragmentShaderRes = CompileShader(
                fragmentShaderSource,
                &fragmentShader,
                GL_FRAGMENT_SHADER);
            if (fragmentShaderRes != GL_TRUE){ // Check for errors.
                std::cout << "Unable to compile fragment shader.\n";
                success = false;
            }
        }
        // If previous steps were successful, continue.
        if (success){
            // Attach fragment shader to GP program.
            glAttachShader(m_programID, fragmentShader);
            // Link the GL program with attached vertex and fragment shaders.
            glLinkProgram(m_programID);
            // Check for errors.
            GLint programSuccess = GL_TRUE;
            glGetProgramiv(
                m_programID,
                GL_LINK_STATUS,
                &programSuccess);
            if (programSuccess != GL_TRUE){
                std::cout << "Error linking shader program.\n";
                success = false;
            }
        }
        // Delete shader resources now that they are linked into the GL program.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return success;
    }
    
    void ShaderProgram::Cleanup() const {
        
        glDeleteProgram(m_programID); // Delete GL program.
    }
    
    GLuint ShaderProgram::CompileShader(
        const GLchar *shader_source,
        GLuint *shader,
        GLenum shader_type) const {
        
        *shader = glCreateShader(shader_type); // Create shader object.
        glShaderSource(*shader, 1, &shader_source, NULL); // Apply shader sources.
        glCompileShader(*shader); // Compile it.
        // Check for compilation errors.
        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv(*shader, GL_COMPILE_STATUS, &shaderCompiled);
        return shaderCompiled;
    }
}
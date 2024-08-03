/*
 * ShaderProgram.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ShaderProgram.h"

namespace jod {
    bool shader_program::create(
        const GLchar *vertex_shader_source,
        const GLchar *fragment_shader_source){
        // To hold the shader IDs.
        GLuint vertex_shader = 0;
        GLuint fragment_shader = 0;
        m_program_id = glCreateProgram(); // Create GL program.
        auto success = true;
        {
            // Compile vertex shader.
            auto vertex_shader_res = compile_shader(
                vertex_shader_source,
                &vertex_shader,
                GL_VERTEX_SHADER);
            if (vertex_shader_res != GL_TRUE){ // Check for errors.
                std::cout << "Unable to compile vertex shader.\n";
                success = false;
            }
        }
        // If previous steps were successful, continue.
        if (success){
            // Attach compiled vertex shader to GL program.
            glAttachShader(m_program_id, vertex_shader);
            // Compile fragment shader.
            auto fragment_shader_res = compile_shader(
                fragment_shader_source,
                &fragment_shader,
                GL_FRAGMENT_SHADER);
            if (fragment_shader_res != GL_TRUE){ // Check for errors.
                std::cout << "Unable to compile fragment shader.\n";
                success = false;
            }
        }
        // If previous steps were successful, continue.
        if (success){
            // Attach fragment shader to GP program.
            glAttachShader(m_program_id, fragment_shader);
            // Link the GL program with attached vertex and fragment shaders.
            glLinkProgram(m_program_id);
            // Check for errors.
            GLint program_success = GL_TRUE;
            glGetProgramiv(
                m_program_id,
                GL_LINK_STATUS,
                &program_success);
            if (program_success != GL_TRUE){
                std::cout << "Error linking shader program.\n";
                success = false;
            }
        }
        // Delete shader resources now that they are linked into the GL program.
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return success;
    }
    
    void shader_program::cleanup()      {
        glDeleteProgram(m_program_id); // Delete GL program.
    }
    
    GLuint shader_program::compile_shader(
        const GLchar *shader_source,
        GLuint *shader,
        GLenum shader_type){
        *shader = glCreateShader(shader_type); // Create shader object.
        glShaderSource(*shader, 1, &shader_source, NULL); // Apply shader sources.
        glCompileShader(*shader); // Compile it.
        // Check for compilation errors.
        GLint shader_compiled = GL_FALSE;
        glGetShaderiv(*shader, GL_COMPILE_STATUS, &shader_compiled);
        return shader_compiled;
    }
}
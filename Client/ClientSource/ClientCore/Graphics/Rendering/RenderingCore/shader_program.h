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
        //! \brief Create a new shader program with provided
        //!        source for vertex and fragment shader.
        //! \param vertex_shader_source Vertex shader source.
        //! \param fragment_shader_source Fragment shader source.
        //! \return bool True if successful, otherwise false.
        bool create(const GLchar *vertex_shader_source,
                    const GLchar *fragment_shader_source);
        
        //! \brief Cleans up allocated resources for this shader program.
        void cleanup();
        
        GLuint m_program_id = 0; //!< Shader program ID.
        
    private:
        GLuint compile_shader(const GLchar *shader_source, GLuint *shader,
                              GLenum shader_type);
    };
}
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
            const GLchar *vertex_shader_source,
            const GLchar *fragment_shader_source);
            
        void cleanup();
        
        GLuint m_program_id = 0;
        
    private:
        GLuint compile_shader(const GLchar *shader_source, GLuint *shader,
                              GLenum shader_type);
    };
}
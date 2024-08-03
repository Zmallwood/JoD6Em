/*
 * RendererBase.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RendererBase.h"
#include "ShaderProgram.h"

namespace jod {
    renderer_base::renderer_base()
        : m_shader_program(std::make_shared<shader_program>()),
        m_vao_ids(std::make_shared<std::vector<GLuint> >()),
        m_vbo_ids(
            std::make_shared<
                std::map<
                    buffer_types,
                    std::shared_ptr<std::map<GLuint, GLuint> > > >()){
    }
    
    GLuint renderer_base::gen_new_vao_id() {
        // Generate new Vertex Array Object.
        GLuint vao_id;
        glGenVertexArraysOES(1, &vao_id);
        m_vao_ids->push_back(vao_id); // Store newly created VAO id.
        return vao_id;
    }
    
    GLuint renderer_base::gen_new_buff_id(
        buffer_types buff_type,
        GLuint vao_id){
        // Generate new Vertex Buffer Object.
        GLuint buff_id;
        glGenBuffers(1, &buff_id);
        // If necessary storing structures not created yet, create them.
        if (!m_vbo_ids->contains(buff_type))
            m_vbo_ids->insert(
                {buff_type, std::make_shared<std::map<GLuint, GLuint> >()});
        // Store newly created VBO id, with the VAO id as one of keys.
        (*(*m_vbo_ids)[buff_type])[vao_id] = buff_id;
        return buff_id; // Return ID for newly created Vertex Buffer Object.
    }
    
    void renderer_base::set_indices_data(
        GLuint indices_vbo_id,
        int num_indices,
        const void *data) const {
        // Bind the VBO buffer that should hold indices data.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id);
        // Set indices data as element array buffer.
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            num_indices * k_num_floats_per_entry.at(buffer_types::indices) *
            sizeof(float),
            data,
            GL_DYNAMIC_DRAW);
    }
    
    void renderer_base::set_data(
        GLuint vbo_id,
        int num_entries,
        const void *data,
        buffer_types buff_type,
        int layout_location) const {
        if (buff_type == buffer_types::bone_ids){
            // Call other method for BoneIDs than other buffer types.
            set_array_buffer_data_int(
                vbo_id,
                num_entries,
                data,
                k_num_floats_per_entry.at(buff_type),
                layout_location);
        }else{
            // Call this function for all buffer types except BoneIDs.
            set_array_buffer_data(
                vbo_id,
                num_entries,
                data,
                k_num_floats_per_entry.at(buff_type),
                layout_location);
        }
    }
    
    void renderer_base::set_array_buffer_data(
        GLuint vbo_id,
        int num_entries,
        const void *data,
        int num_floats_per_entry,
        int layout_location) const {
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id); // Bind the VBO for the provided VBO id.
        // Set the buffer data as an array buffer.
        glBufferData(
            GL_ARRAY_BUFFER,
            num_entries * num_floats_per_entry * sizeof(float),
            data,
            GL_DYNAMIC_DRAW);
        if (layout_location >= 0){ // Is valid layout location?
            // Configure layout float float values.
            glVertexAttribPointer(
                layout_location,
                num_floats_per_entry,
                GL_FLOAT,
                GL_FALSE,
                0,
                (const GLvoid *)0);
            glEnableVertexAttribArray(layout_location); // Enable layout.
        }
    }
    
    void renderer_base::set_array_buffer_data_int(
        GLuint vbo_id,
        int num_entries,
        const void *data,
        int num_floats_per_entry,
        int layout_location) const {
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id); // Bind the VBO for the provided VBO id.
        // Set the buffer data as an array buffer.
        glBufferData(
            GL_ARRAY_BUFFER,
            num_entries * num_floats_per_entry * sizeof(int),
            data,
            GL_DYNAMIC_DRAW);
        if (layout_location >= 0){ // Is valid layout location?
            glEnableVertexAttribArray(3); // Enable generic vertex attribute.
            // // Configure layout for int values.
            // glVertexAttribIPointer(layoutLocation, numFloatsPerEntry, GL_INT, 0, (const GLvoid*)0);
            // Configure layout for float values.
            glVertexAttribPointer(
                layout_location,
                num_floats_per_entry,
                GL_INT,
                GL_FALSE,
                0,
                (const GLvoid *)0);
            glEnableVertexAttribArray(layout_location); // Enable layout.
        }
    }
    
    GLuint renderer_base::get_uniform_location(
        std::string_view variable_name) {
        // Get layout location of uniform variable in the shader.
        return glGetUniformLocation(
            m_shader_program->m_program_id,
            variable_name.data());
    }
    
    void renderer_base::use_vao_begin(GLuint vao_id) const {
        // Start using shader program and provided VAO.
        glUseProgram(m_shader_program->m_program_id);
        glBindVertexArrayOES(vao_id);
    }
    
    GLuint renderer_base::get_buff_id(
        buffer_types buff_type,
        GLuint vao_id) const {
        return m_vbo_ids->at(buff_type)->at(vao_id); // Returns the buffer of provided type and VAO id.
    }
    
    void renderer_base::update_indices_data(
        GLuint indices_vbo_id,
        std::vector<int> &indices) const {
        // Bind VBO with provided id, being an element array buffer.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id);
        // Set the buffer data.
        glBufferSubData(
            GL_ELEMENT_ARRAY_BUFFER,
            0,
            sizeof(float) * indices.size(),
            indices.data());
    }
    
    void renderer_base::update_array_buffer_data(
        GLuint vbo_id,
        std::vector<float> &data,
        int num_floats_per_entry,
        int layout_location) const {
        // Bind VBO with provided id, being an array buffer.
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
        // Set the buffer data.
        glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            sizeof(float) * data.size(),
            data.data());
        glVertexAttribPointer(
            layout_location,
            num_floats_per_entry,
            GL_FLOAT,
            GL_FALSE,
            0,
            (const GLvoid *)0);
        glEnableVertexAttribArray(layout_location); // Enable layout.
    }
    
    void renderer_base::update_array_buffer_data_int(
        GLuint vbo_id,
        std::vector<float> &data,
        int num_floats_per_entry,
        int layout_location) const {
        // Bind VBO with provided id, being an array buffer.
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
        // Set the buffer data.
        glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            sizeof(int) * data.size(),
            data.data());
        // // Configure layout for int values.
        // glVertexAttribIPointer(layoutLocation, numFloatsPerEntry, GL_INT, 0, (const GLvoid *)0);
        glVertexAttribPointer(
            layout_location,
            num_floats_per_entry,
            GL_INT,
            GL_FALSE,
            0,
            (const GLvoid *)0);
        glEnableVertexAttribArray(layout_location); // Enable layout.
    }
    
    void renderer_base::update_data(
        GLuint vbo_id,
        std::vector<float> &data,
        buffer_types buff_type,
        int layout_location) const {
        if (buff_type == buffer_types::bone_ids){ // Does the buffer hold BoneID data?
            // If so, update buffer with int data.
            update_array_buffer_data_int(
                vbo_id,
                data,
                k_num_floats_per_entry.at(buff_type),
                layout_location);
        } else{
            // Else, update with float data.
            update_array_buffer_data(
                vbo_id,
                data,
                k_num_floats_per_entry.at(buff_type),
                layout_location);
        }
    }
    
    void renderer_base::use_vao_end() const {
        glBindVertexArrayOES(0); // Unbind currently used VAO.
        glUseProgram(0); // Stop using shader program.
    }
    
    void renderer_base::cleanup_base() const {
        for (auto &buff_type : *m_vbo_ids) // Loop through all keys of buffer types.
            for (auto &buffer_entry : (*buff_type.second)) // Loop through all keys of VAO ids.
                glDeleteBuffers(1, &buffer_entry.second); // Delete every VBO.
        for (auto vao_id : *m_vao_ids) // Loop through all VAO ids.
            glDeleteVertexArraysOES(1, &vao_id); // And delete them.
        m_shader_program->cleanup(); // Finally, clean up shader proram.
    }
}
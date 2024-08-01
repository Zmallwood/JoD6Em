// Copyright (c) 2024 Andreas Åkerberg.

#include "rendering_core.h"

namespace jod {
    bool
    shader_program::create(
        const GLchar *vertexShaderSource,
        const GLchar *fragmentShaderSource){
        // To hold the shader IDs.
        GLuint vertexShader = 0;
        GLuint fragmentShader = 0;
        m_programID = glCreateProgram(); // Create GL program.
        auto success = true;
        {
            // Compile vertex shader.
            auto vertexShaderRes = compile_shader(
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
            glAttachShader(
                m_programID,
                vertexShader);
            // Compile fragment shader.
            auto fragmentShaderRes = compile_shader(
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
            glAttachShader(
                m_programID,
                fragmentShader);
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
    void
    shader_program::cleanup(){
        glDeleteProgram(m_programID); // Delete GL program.
    }
    GLuint
    shader_program::compile_shader(
        const GLchar *shaderSource,
        GLuint *shader,
        GLenum shaderType){
        *shader = glCreateShader(shaderType); // Create shader object.
        glShaderSource(
            *shader,
            1,
            &shaderSource,
            NULL);                                       // Apply shader sources.
        glCompileShader(*shader); // Compile it.
        // Check for compilation errors.
        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv(
            *shader,
            GL_COMPILE_STATUS,
            &shaderCompiled);
        return shaderCompiled;
    }
    renderer_base::renderer_base()
        : m_shaderProgram(std::make_shared<shader_program>()),
        m_VAOIDs(std::make_shared<std::vector<GLuint> >()),
        m_VBOIDs(
            std::make_shared<std::map<buffer_types, std::shared_ptr<std::map<GLuint, GLuint> > > >()){
    }
    GLuint
    renderer_base::gen_new_vao_id(){
        // Generate new Vertex Array Object.
        GLuint VAOID;
        glGenVertexArraysOES(
            1,
            &VAOID);
        m_VAOIDs->push_back(VAOID); // Store newly created VAO id.
        return VAOID;
    }
    GLuint
    renderer_base::gen_new_buff_id(buffer_types buffType,
                                   GLuint VAOID){
        // Generate new Vertex Buffer Object.
        GLuint buffID;
        glGenBuffers(
            1,
            &buffID);
        // If necessary storing structures not created yet, create them.
        if (!m_VBOIDs->contains(buffType))
            m_VBOIDs->insert({buffType, std::make_shared<std::map<GLuint, GLuint> >()});
        // Store newly created VBO id, with the VAO id as one of keys.
        (*(*m_VBOIDs)[buffType])[VAOID] = buffID;
        return buffID; // Return ID for newly created Vertex Buffer Object.
    }
    void
    renderer_base::set_indices_data(GLuint indicesVBOID,
                                    int numIndices,
                                    const void *data) const {
        // Bind the VBO buffer that should hold indices data.
        glBindBuffer(
            GL_ELEMENT_ARRAY_BUFFER,
            indicesVBOID);
        // Set indices data as element array buffer.
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            numIndices * k_numFloatsPerEntry.at(buffer_types::Indices) * sizeof(float),
            data,
            GL_DYNAMIC_DRAW);
    }
    void
    renderer_base::set_data(
        GLuint VBOID,
        int numEntries,
        const void *data,
        buffer_types buffType,
        int layoutLocation) const {
        if (buffType == buffer_types::BoneIDs){
            // Call other method for BoneIDs than other buffer types.
            set_array_buffer_data_int(
                VBOID,
                numEntries,
                data,
                k_numFloatsPerEntry.at(buffType),
                layoutLocation);
        }else{
            // Call this function for all buffer types except BoneIDs.
            set_array_buffer_data(
                VBOID,
                numEntries,
                data,
                k_numFloatsPerEntry.at(buffType),
                layoutLocation);
        }
    }
    void
    renderer_base::set_array_buffer_data(
        GLuint VBOID,
        int numEntries,
        const void *data,
        int numFloatsPerEntry,
        int layoutLocation) const {
        glBindBuffer(GL_ARRAY_BUFFER,
                     VBOID);                  // Bind the VBO for the provided VBO id.
        // Set the buffer data as an array buffer.
        glBufferData(
            GL_ARRAY_BUFFER,
            numEntries * numFloatsPerEntry * sizeof(float),
            data,
            GL_DYNAMIC_DRAW);
        if (layoutLocation >= 0){ // Is valid layout location?
            // Configure layout float float values.
            glVertexAttribPointer(
                layoutLocation,
                numFloatsPerEntry,
                GL_FLOAT,
                GL_FALSE,
                0,
                (const GLvoid *)0);
            glEnableVertexAttribArray(layoutLocation); // Enable layout.
        }
    }
    void
    renderer_base::set_array_buffer_data_int(
        GLuint VBOID,
        int numEntries,
        const void *data,
        int numFloatsPerEntry,
        int layoutLocation) const {
        glBindBuffer(
            GL_ARRAY_BUFFER,
            VBOID);                           // Bind the VBO for the provided VBO id.
        // Set the buffer data as an array buffer.
        glBufferData(
            GL_ARRAY_BUFFER,
            numEntries * numFloatsPerEntry * sizeof(int),
            data,
            GL_DYNAMIC_DRAW);
        if (layoutLocation >= 0){ // Is valid layout location?
            glEnableVertexAttribArray(3); // Enable generic vertex attribute.
            // // Configure layout for int values.
            // glVertexAttribIPointer(layoutLocation, numFloatsPerEntry, GL_INT, 0, (const GLvoid*)0);
            // Configure layout for float values.
            glVertexAttribPointer(
                layoutLocation,
                numFloatsPerEntry,
                GL_INT,
                GL_FALSE,
                0,
                (const GLvoid *)0);
            // Enable layout.
            glEnableVertexAttribArray(layoutLocation);
        }
    }
    GLuint
    renderer_base::get_uniform_location(std::string_view variableName){
        // Get layout location of uniform variable in the shader.
        return glGetUniformLocation(
            m_shaderProgram->m_programID,
            variableName.data());
    }
    void
    renderer_base::use_vao_begin(GLuint VAOID) const {
        // Start using shader program and provided VAO.
        glUseProgram(m_shaderProgram->m_programID);
        glBindVertexArrayOES(VAOID);
    }
    GLuint
    renderer_base::get_buff_id(
        buffer_types buffType,
        GLuint VAOID) const {
        return m_VBOIDs->at(buffType)->at(VAOID); // Returns the buffer of provided type and VAO id.
    }
    void
    renderer_base::update_indices_data(
        GLuint indicesVBOID,
        std::vector<int> &indices) const {
        // Bind VBO with provided id, being an element array buffer.
        glBindBuffer(
            GL_ELEMENT_ARRAY_BUFFER,
            indicesVBOID);
        // Set the buffer data.
        glBufferSubData(
            GL_ELEMENT_ARRAY_BUFFER,
            0,
            sizeof(float) * indices.size(),
            indices.data());
    }
    void
    renderer_base::update_array_buffer_data(
        GLuint VBOID,
        std::vector<float> &data,
        int numFloatsPerEntry,
        int layoutLocation) const {
        // Bind VBO with provided id, being an array buffer.
        glBindBuffer(
            GL_ARRAY_BUFFER,
            VBOID);
        // Set the buffer data.
        glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            sizeof(float) * data.size(),
            data.data());
        glVertexAttribPointer(
            layoutLocation,
            numFloatsPerEntry,
            GL_FLOAT,
            GL_FALSE,
            0,
            (const GLvoid *)0);
        glEnableVertexAttribArray(layoutLocation); // Enable layout.
    }
    void
    renderer_base::update_array_buffer_data_int(
        GLuint VBOID,
        std::vector<float> &data,
        int numFloatsPerEntry,
        int layoutLocation) const {
        // Bind VBO with provided id, being an array buffer.
        glBindBuffer(
            GL_ARRAY_BUFFER,
            VBOID);
        // Set the buffer data.
        glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            sizeof(int) * data.size(),
            data.data());
        // // Configure layout for int values.
        // glVertexAttribIPointer(layoutLocation, numFloatsPerEntry, GL_INT, 0, (const GLvoid *)0);
        glVertexAttribPointer(
            layoutLocation,
            numFloatsPerEntry,
            GL_INT,
            GL_FALSE,
            0,
            (const GLvoid *)0);
        glEnableVertexAttribArray(layoutLocation); // Enable layout.
    }
    
    void
    renderer_base::update_data(
        GLuint VBOID,
        std::vector<float> &data,
        buffer_types buffType,
        int layoutLocation) const {
        if (buffType == buffer_types::BoneIDs){ // Does the buffer hold BoneID data?
            // If so, update buffer with int data.
            update_array_buffer_data_int(
                VBOID,
                data,
                k_numFloatsPerEntry.at(buffType),
                layoutLocation);
        } else{
            // Else, update with float data.
            update_array_buffer_data(
                VBOID,
                data,
                k_numFloatsPerEntry.at(buffType),
                layoutLocation);
        }
    }
    void
    renderer_base::use_vao_end() const {
        glBindVertexArrayOES(0); // Unbind currently used VAO.
        glUseProgram(0); // Stop using shader program.
    }
    void
    renderer_base::cleanup_base() const {
        for (auto &buffType : *m_VBOIDs) // Loop through all keys of buffer types.
            for (auto &bufferEntry : (*buffType.second)) // Loop through all keys of VAO ids.
                glDeleteBuffers(
                    1,
                    &bufferEntry.second);                // Delete every VBO.
        for (auto VAOID : *m_VAOIDs) // Loop through all VAO ids.
            glDeleteVertexArraysOES(
                1,
                &VAOID);                        // And delete them.
        m_shaderProgram->cleanup(); // Finally, clean up shader proram.
    }
}
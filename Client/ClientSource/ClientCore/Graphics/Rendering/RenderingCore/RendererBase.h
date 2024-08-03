/*
 * RendererBase.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "BufferTypes.h"

namespace jod {      
    class shader_program;

    //! \brief Functions as a base class for all renderers providing shared base functionality.
    class renderer_base {
    protected:
        //! \brief Construct a new Renderer Base object, creating shader program and buffer storing
        //!        structures.
        renderer_base();
        
        //! \brief new Vertex Array Object and returns its ID.
        //! \return GLuint The ID of a new VAO.
        GLuint gen_new_vao_id();
        
        //! \brief Generate a new Vertex Buffer Object and returns its ID.
        //! \param buff_type Type of buffer the data will hold.
        //! \param vao_id The ID of the Vertex Array Object to which the new buffer is associated.
        //! \return GLuint The ID of the new VBO.
        GLuint gen_new_buff_id(buffer_types buff_type, GLuint vao_id);
        
        //! \brief Set indices data for a VBO.
        //! \param indices_vbo_id The VBO ID associated with the indices data.
        //! \param num_indices Number of indices to set.
        //! \param data Indices data.
        void set_indices_data(
            GLuint indices_vbo_id,
            int num_indices,
            const void *data) const;
        
        //! \brief Set buffer data for a VBO.
        //! \param vbo_id The VBO ID associated with the data.
        //! \param num_entries Number of entries to set.
        //! \param data The buffer data.
        //! \param buff_type Type of buffer the data will hold.
        //! \param layout_location Location in the shader.
        void set_data(
            GLuint vbo_id,
            int num_entries,
            const void *data,
            buffer_types buff_type,
            int layout_location = -1) const;
        
        //! \brief Get layout location in the shader of an uniform variable.
        //! \param variable_name Name of variable to obtain location for.
        //! \return GLuint Location index.
        GLuint get_uniform_location(std::string_view variable_name);
        
        //! \brief Start using a Vertex Array Object.
        //! \param vao_id ID of the Vertex Array Object to start using.
        void use_vao_begin(GLuint vao_id) const;
        
        //! \brief Get the ID of a Vertex Buffer Object of a specific type associated with a specific
        //!        Vertex Array Object.
        //! \param buff_type The type of buffer to get the ID for.
        //! \param vao_id The Vertex Array Object to get the ID for.
        //! \return GLuint The ID of the Vertex Buffer Object.
        GLuint get_buff_id(buffer_types buff_type, GLuint vao_id) const;
        
        //! \brief Update indices data.
        //! \param indices_vbo_id The ID of the indices VBO to update.
        //! \param indices Indices data to update with.
        void update_indices_data(GLuint indices_vbo_id,
                                 std::vector<int> &indices) const;
        
        //! \brief Update data in an Vertex Buffer Object holding a specific buffer type and at a
        //!        specific layout location in the shader.
        //! \param vbo_id The ID of the Vertex Buffer Object to update.
        //! \param data The data to update with.
        //! \param buff_type The type of data the buffer holds.
        //! \param layout_location The layout location in the shader for the data.
        void update_data(
            GLuint vbo_id,
            std::vector<float> &data,
            buffer_types buff_type,
            int layout_location) const;
        
        //! \brief Stop using the current Vertex Array Object.
        void use_vao_end() const;
        
        //! \brief Delete all buffers, the Vertex Array Object and cleanup the shader program.
        void cleanup_base() const;
        
        std::shared_ptr<shader_program> m_shader_program; //!< The shader program used for this renderer object.
        
    private:
        //! \brief Apply data to an array buffer of float type.
        //! \param vbo_id VBO ID to set the data for.
        //! \param num_entries Number of entries to set.
        //! \param data The actual data.
        //! \param num_floats_per_entry Number of flots per entry.
        //! \param layout_location Layout location of the data in the shader.
        void set_array_buffer_data(
            GLuint vbo_id,
            int num_entries,
            const void *data,
            int num_floats_per_entry,
            int layout_location = -1) const;
        
        //! \brief Apply data to an array buffer of int type.
        //! \param vbo_id VBO ID to set the data for.
        //! \param num_entries Number of entries to set.
        //! \param data The actual data.
        //! \param num_floats_per_entry Number of flots per entry.
        //! \param layout_location Layout location of the data in the shader.
        void set_array_buffer_data_int(
            GLuint vbo_id,
            int num_entries,
            const void *data,
            int num_floats_per_entry,
            int layout_location = -1) const;
        
        //! \brief Update data to an array buffer of float type.
        //! \param vbo_id VBO ID to update the data for.
        //! \param data The actual data.
        //! \param num_floats_per_entry Number of flots per entry.
        //! \param layout_location Layout location of the data in the shader.
        void update_array_buffer_data(
            GLuint vbo_id,
            std::vector<float> &data,
            int num_floats_per_entry,
            int layout_location) const;
        
        //! \brief Update data to an array buffer of int type.
        //! \param vbo_id VBO ID to update the data for.
        //! \param data The actual data.
        //! \param num_floats_per_entry Number of flots per entry.
        //! \param layout_location Layout location of the data in the shader.
        void update_array_buffer_data_int(
            GLuint vbo_id,
            std::vector<float> &data,
            int num_floats_per_entry,
            int layout_location) const;
        
        std::shared_ptr<std::vector<GLuint> > m_vao_ids; //!< Stores IDs of all Vertex Array Objects.
        
        std::shared_ptr<
            std::map<
                buffer_types, std::shared_ptr<
                    std::map<
                        GLuint,
                        GLuint> > > >
        m_vbo_ids; //!< Stores IDs of all Vertex Buffer Objects.
        
        inline static const auto
            k_num_floats_per_entry = std::map<buffer_types, int>{ //!< Predefined constants of number of floats for different entry types.
            {buffer_types::indices, 1}, {buffer_types::positions_2d, 2},
            {buffer_types::positions_3d, 3},
            {buffer_types::colors, 4},  {buffer_types::uvs, 2},
            {buffer_types::normals, 3},
            {buffer_types::bone_ids, 4}, {buffer_types::weights, 4}};
    };
}
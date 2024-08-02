// renderer_base.h
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>

#pragma once

#include "buffer_types.h"

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
        //! \param buffType Type of buffer the data will hold.
        //! \param VAOID The ID of the Vertex Array Object to which the new buffer is associated.
        //! \return GLuint The ID of the new VBO.
        GLuint gen_new_buff_id(buffer_types buffType, GLuint VAOID);
        
        //! \brief Set indices data for a VBO.
        //! \param indicesVBOID The VBO ID associated with the indices data.
        //! \param numIndices Number of indices to set.
        //! \param data Indices data.
        void set_indices_data(
            GLuint indicesVBOID,
            int numIndices,
            const void *data) const;
        
        //! \brief Set buffer data for a VBO.
        //! \param VBOID The VBO ID associated with the data.
        //! \param numEntries Number of entries to set.
        //! \param data The buffer data.
        //! \param buffType Type of buffer the data will hold.
        //! \param layoutLocation Location in the shader.
        void set_data(
            GLuint VBOID,
            int numEntries,
            const void *data,
            buffer_types buffType,
            int layoutLocation = -1) const;
        
        //! \brief Get layout location in the shader of an uniform variable.
        //! \param variableName Name of variable to obtain location for.
        //! \return GLuint Location index.
        GLuint get_uniform_location(std::string_view variableName);
        
        //! \brief Start using a Vertex Array Object.
        //! \param VAOID ID of the Vertex Array Object to start using.
        void use_vao_begin(GLuint VAOID) const;
        
        //! \brief Get the ID of a Vertex Buffer Object of a specific type associated with a specific
        //!        Vertex Array Object.
        //! \param buffType The type of buffer to get the ID for.
        //! \param VAOID The Vertex Array Object to get the ID for.
        //! \return GLuint The ID of the Vertex Buffer Object.
        GLuint get_buff_id(buffer_types buffType, GLuint VAOID) const;
        
        //! \brief Update indices data.
        //! \param indicesVBOID The ID of the indices VBO to update.
        //! \param indices Indices data to update with.
        void update_indices_data(GLuint indicesVBOID,
                                 std::vector<int> &indices) const;
        
        //! \brief Update data in an Vertex Buffer Object holding a specific buffer type and at a
        //!        specific layout location in the shader.
        //! \param VBOID The ID of the Vertex Buffer Object to update.
        //! \param data The data to update with.
        //! \param buffType The type of data the buffer holds.
        //! \param layoutLocation The layout location in the shader for the data.
        void update_data(
            GLuint VBOID,
            std::vector<float> &data,
            buffer_types buffType,
            int layoutLocation) const;
        
        //! \brief Stop using the current Vertex Array Object.
        void use_vao_end() const;
        
        //! \brief Delete all buffers, the Vertex Array Object and cleanup the shader program.
        void cleanup_base() const;
        
        std::shared_ptr<shader_program> m_shaderProgram; //!< The shader program used for this renderer object.
        
    private:
        //! \brief Apply data to an array buffer of float type.
        //! \param VBOID VBO ID to set the data for.
        //! \param numEntries Number of entries to set.
        //! \param data The actual data.
        //! \param numFloatsPerEntry Number of flots per entry.
        //! \param layoutLocation Layout location of the data in the shader.
        void set_array_buffer_data(
            GLuint VBOID,
            int numEntries,
            const void *data,
            int numFloatsPerEntry,
            int layoutLocation = -1) const;
        
        //! \brief Apply data to an array buffer of int type.
        //! \param VBOID VBO ID to set the data for.
        //! \param numEntries Number of entries to set.
        //! \param data The actual data.
        //! \param numFloatsPerEntry Number of flots per entry.
        //! \param layoutLocation Layout location of the data in the shader.
        void set_array_buffer_data_int(
            GLuint VBOID,
            int numEntries,
            const void *data,
            int numFloatsPerEntry,
            int layoutLocation = -1) const;
        
        //! \brief Update data to an array buffer of float type.
        //! \param VBOID VBO ID to update the data for.
        //! \param data The actual data.
        //! \param numFloatsPerEntry Number of flots per entry.
        //! \param layoutLocation Layout location of the data in the shader.
        void update_array_buffer_data(
            GLuint VBOID,
            std::vector<float> &data,
            int numFloatsPerEntry,
            int layoutLocation) const;
        
        //! \brief Update data to an array buffer of int type.
        //! \param VBOID VBO ID to update the data for.
        //! \param data The actual data.
        //! \param numFloatsPerEntry Number of flots per entry.
        //! \param layoutLocation Layout location of the data in the shader.
        void update_array_buffer_data_int(
            GLuint VBOID,
            std::vector<float> &data,
            int numFloatsPerEntry,
            int layoutLocation) const;
        
        std::shared_ptr<std::vector<GLuint> > m_VAOIDs; //!< Stores IDs of all Vertex Array Objects.
        
        std::shared_ptr<
            std::map<
                buffer_types, std::shared_ptr<
                    std::map<
                        GLuint,
                        GLuint> > > >
        m_VBOIDs; //!< Stores IDs of all Vertex Buffer Objects.
        
        inline static const auto
            k_numFloatsPerEntry = std::map<buffer_types, int>{ //!< Predefined constants of number of floats for different entry types.
            {buffer_types::Indices, 1}, {buffer_types::Positions2D, 2},
            {buffer_types::Positions3D, 3},
            {buffer_types::Colors, 4},  {buffer_types::UVs, 2},
            {buffer_types::Normals, 3},
            {buffer_types::BoneIDs, 4}, {buffer_types::Weights, 4}};
    };
}
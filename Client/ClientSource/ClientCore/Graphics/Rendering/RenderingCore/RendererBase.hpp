/*
 * RendererBase.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "BufferTypes.hpp"

namespace JoD {
    
    class ShaderProgram;
    
    ///
    /// Functions as a base class for all renderers providing shared base functionality.
    ///
    class RendererBase {
        
      protected:
        ///
        /// Construct a new Renderer Base object, creating shader program and buffer storing
        /// structures.
        ///
        RendererBase();
        
        ///
        /// Create new Vertex Array Object and returns its ID.
        ///
        /// @return GLuint The ID of a new VAO.
        ///
        GLuint GenNewVAOID();
        
        ///
        /// Generate a new Vertex Buffer Object and returns its ID.
        ///
        /// @param buffType Type of buffer the data will hold.
        /// @param VAOID The ID of the Vertex Array Object to which the new buffer is associated.
        /// @return GLuint The ID of the new VBO.
        ///
        GLuint GenNewBuffID(BufferTypes buffType, GLuint VAOID);
        
        ///
        /// Set indices data for a VBO.
        ///
        /// @param indicesVBOID The VBO ID associated with the indices data.
        /// @param numIndices Number of indices to set.
        /// @param data Indices data.
        ///
        void SetIndicesData(
            GLuint indicesVBOID,
            int numIndices,
            const void *data) const;
        
        ///
        /// Set buffer data for a VBO.
        ///
        /// @param VBOID The VBO ID associated with the data.
        /// @param numEntries Number of entries to set.
        /// @param data The buffer data.
        /// @param buffType Type of buffer the data will hold.
        /// @param layoutLocation Location in the shader.
        ///
        void SetData(
            GLuint VBOID,
            int numEntries,
            const void *data,
            BufferTypes buffType,
            int layoutLocation = -1) const;
        
        ///
        /// Get layout location in the shader of an uniform variable.
        ///
        /// @param variableName Name of variable to obtain location for.
        /// @return GLuint Location index.
        ///
        GLuint GetUniformLocation(std::string_view variableName) const;
        
        ///
        /// Start using a Vertex Array Object.
        ///
        /// @param VAOID ID of the Vertex Array Object to start using.
        ///
        void UseVAOBegin(GLuint VAOID) const;
        
        ///
        /// Get the ID of a Vertex Buffer Object of a specific type associated with a specific
        /// Vertex Array Object.
        ///
        /// @param buffType The type of buffer to get the ID for.
        /// @param VAOID The Vertex Array Object to get the ID for.
        /// @return GLuint The ID of the Vertex Buffer Object.
        ///
        GLuint GetBuffID(BufferTypes buffType, GLuint VAOID) const;
        
        ///
        /// Update indices data.
        ///
        /// @param indicesVBOID The ID of the indices VBO to update.
        /// @param indices Indices data to update with.
        ///
        void UpdateIndicesData(GLuint indicesVBOID,
                               std::vector<int> &indices) const;
        
        ///
        /// Update data in an Vertex Buffer Object holding a specific buffer type and at a
        /// specific layout location in the shader.
        ///
        /// @param VBOID The ID of the Vertex Buffer Object to update.
        /// @param data The data to update with.
        /// @param buffType The type of data the buffer holds.
        /// @param layoutLocation The layout location in the shader for the data.
        ///
        void UpdateData(
            GLuint VBOID,
            const std::vector<float> &data,
            BufferTypes buffType,
            int layoutLocation) const;
        
        ///
        /// Stop using the current Vertex Array Object.
        ///
        void UseVAOEnd() const;
        
        ///
        /// Delete all buffers, the Vertex Array Object and cleanup the shader program.
        ///
        void CleanupBase() const;
        
      protected:
        const std::unique_ptr<ShaderProgram>& GetShaderProgram() {
            
            return m_shaderProgram;
        }
        
      private:
        ///
        /// Apply data to an array buffer of float type.
        ///
        /// @param VBOID VBO ID to set the data for.
        /// @param numEntries Number of entries to set.
        /// @param data The actual data.
        /// @param numFloatsPerEntry Number of flots per entry.
        /// @param layoutLocation Layout location of the data in the shader.
        ///
        void SetArrayBufferData(
            GLuint VBOID,
            int numEntries,
            const void *data,
            int numFloatsPerEntry,
            int layoutLocation = -1) const;
        
        ///
        /// Apply data to an array buffer of int type.
        ///
        /// @param VBOID VBO ID to set the data for.
        /// @param numEntries Number of entries to set.
        /// @param data The actual data.
        /// @param numFloatsPerEntry Number of flots per entry.
        /// @param layoutLocation Layout location of the data in the shader.
        ///
        void SetArrayBufferDataInt(
            GLuint VBOID,
            int numEntries,
            const void *data,
            int numFloatsPerEntry,
            int layoutLocation = -1) const;
        
        ///
        /// Update data to an array buffer of float type.
        ///
        /// @param VBOID VBO ID to update the data for.
        /// @param data The actual data.
        /// @param numFloatsPerEntry Number of flots per entry.
        /// @param layoutLocation Layout location of the data in the shader.
        ///
        void UpdateArrayBufferData(
            GLuint VBOID,
            const std::vector<float> &data,
            int numFloatsPerEntry,
            int layoutLocation) const;
        
        ///
        /// Update data to an array buffer of int type.
        ///
        /// @param VBOID VBO ID to update the data for.
        /// @param data The actual data.
        /// @param numFloatsPerEntry Number of flots per entry.
        /// @param layoutLocation Layout location of the data in the shader.
        ///
        void UpdateArrayBufferDataInt(
            GLuint VBOID,
            const std::vector<float> &data,
            int numFloatsPerEntry,
            int layoutLocation) const;
        
        std::vector<GLuint> m_VAOIDs;  ///< Stores IDs of all Vertex Array Objects.
        std::map<BufferTypes, std::map<GLuint,GLuint>>
        m_VBOIDs; ///< Stores IDs of all Vertex Buffer Objects.
        std::unique_ptr<ShaderProgram> m_shaderProgram; ///< The shader program used for this renderer object.
    };
}
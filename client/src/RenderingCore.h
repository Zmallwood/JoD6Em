// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
  /**
   * @brief Available types of GL buffers that can be created.
   *
   */
  enum class BufferTypes
  {
    Indices,

    Positions2D,

    Positions3D,

    Colors,

    UVs,

    Normals,

    BoneIDs,

    Weights,

    Misc
  };

  /**
   * @brief OpenGL shader program object.
   *
   */
  class ShaderProgram
  {
   public:
    bool Create(const GLchar *vertexShaderSource, const GLchar *fragmentShaderSource);

    void Cleanup();

    GLuint m_programID = 0;

   private:
    GLuint CompileShader(const GLchar *shaderSource, GLuint *shader, GLenum shaderType);
  };

  /**
   * @brief Functions as a base class for all renderers providing shared base functionality.
   *
   */
  class RendererBase
  {
   protected:
    /**
     * @brief Construct a new Renderer Base object, creating shader program and buffer storing
     * structures.
     *
     */
    RendererBase();

    /**
     * @brief Generates a new Vertex Array Object and returns its ID.
     *
     * @return GLuint The ID of a new VAO.
     */
    GLuint GenNewVAOID();

    /**
     * @brief Generate a new Vertex Buffer Object and returns its ID.
     *
     * @param buffType Type of buffer the data will hold.
     * @param VAOID The ID of the Vertex Array Object to which the new buffer is associated.
     * @return GLuint The ID of the new VBO.
     */
    GLuint GenNewBuffID(BufferTypes buffType, GLuint VAOID);

    /**
     * @brief Set indices data for a VBO.
     *
     * @param indicesVBOID The VBO ID associated with the indices data.
     * @param numIndices Number of indices to set.
     * @param data Indices data.
     */
    void SetIndicesData(GLuint indicesVBOID, int numIndices, const void *data) const;

    /**
     * @brief Set buffer data for a VBO.
     *
     * @param VBOID The VBO ID associated with the data.
     * @param numEntries Number of entries to set.
     * @param data The buffer data.
     * @param buffType Type of buffer the data will hold.
     * @param layoutLocation Location in the shader.
     */
    void SetData(GLuint VBOID, int numEntries, const void *data, BufferTypes buffType,
                 int layoutLocation = -1) const;

    /**
     * @brief Get layout location in the shader of an uniform variable.
     *
     * @param variableName Name of variable to obtain location for.
     * @return GLuint Location index.
     */
    GLuint GetUniformLocation(std::string_view variableName);

    /**
     * @brief Start using a Vertex Array Object.
     *
     * @param VAOID ID of the Vertex Array Object to start using.
     */
    void UseVAOBegin(GLuint VAOID) const;

    /**
     * @brief Get the ID of a Vertex Buffer Object of a specific type associated with a specific
     * Vertex Array Object.
     *
     * @param buffType The type of buffer to get the ID for.
     * @param VAOID The Vertex Array Object to get the ID for.
     * @return GLuint The ID of the Vertex Buffer Object.
     */
    GLuint GetBuffID(BufferTypes buffType, GLuint VAOID) const;

    /**
     * @brief Update indices data.
     *
     * @param indicesVBOID The ID of the indices VBO to update.
     * @param indices Indices data to update with.
     */
    void UpdateIndicesData(GLuint indicesVBOID, std::vector<int> &indices) const;

    /**
     * @brief Update data in an Vertex Buffer Object holding a specific buffer type and at a
     * specific layout location in the shader.
     *
     * @param VBOID The ID of the Vertex Buffer Object to update.
     * @param data The data to update with.
     * @param buffType The type of data the buffer holds.
     * @param layoutLocation The layout location in the shader for the data.
     */
    void UpdateData(GLuint VBOID, std::vector<float> &data, BufferTypes buffType,
                    int layoutLocation) const;

    /**
     * @brief Stop using the current Vertex Array Object.
     *
     */
    void UseVAOEnd() const;

    /**
     * @brief Delete all buffers, the Vertex Array Object and cleanup the shader program.
     *
     */
    void CleanupBase() const;

    /**
     * @brief The shader program used for this renderer object.
     *
     */
    std::shared_ptr<ShaderProgram> m_shaderProgram;

   private:
    void SetArrayBufferData(GLuint VBOID, int numEntries, const void *data, int numFloatsPerEntry,
                            int layoutLocation = -1) const;

    void SetArrayBufferDataInt(GLuint VBOID, int numEntries, const void *data,
                               int numFloatsPerEntry, int layoutLocation = -1) const;

    void UpdateArrayBufferData(GLuint VBOID, std::vector<float> &data, int numFloatsPerEntry,
                               int layoutLocation) const;

    void UpdateArrayBufferDataInt(GLuint VBOID, std::vector<float> &data, int numFloatsPerEntry,
                                  int layoutLocation) const;

    std::shared_ptr<std::vector<GLuint>> m_VAOIDs;

    std::shared_ptr<std::map<BufferTypes, std::shared_ptr<std::map<GLuint, GLuint>>>> m_VBOIDs;

    inline static const auto k_numFloatsPerEntry = std::map<BufferTypes, int>{
        {BufferTypes::Indices, 1}, {BufferTypes::Positions2D, 2}, {BufferTypes::Positions3D, 3},
        {BufferTypes::Colors, 4},  {BufferTypes::UVs, 2},         {BufferTypes::Normals, 3},
        {BufferTypes::BoneIDs, 4}, {BufferTypes::Weights, 4}};
  };
}
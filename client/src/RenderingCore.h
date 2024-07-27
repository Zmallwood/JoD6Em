// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
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

    class ShaderProgram
    {
      public:
        bool Create(const GLchar *vertexShaderSource, const GLchar *fragmentShaderSource);
        void Cleanup();

        GLuint m_programID = 0;

      private:
        GLuint CompileShader(const GLchar *shaderSource, GLuint *shader, GLenum shaderType);
    };

    class RendererBase
    {
      protected:
        RendererBase();
        GLuint GenNewVAOID();
        GLuint GenNewBuffID(BufferTypes buffType, GLuint VAOID);
        void SetIndicesData(GLuint indicesVBOID, int numIndices, const void *data) const;
        void SetData(GLuint VBOID, int numEntries, const void *data, BufferTypes buffType,
                     int layoutLocation = -1) const;
        GLuint GetUniformLocation(std::string_view variableName);
        void UseVAOBegin(GLuint VAOID) const;
        GLuint GetBuffID(BufferTypes buffType, GLuint VAOID) const;
        void UpdateIndicesData(GLuint indicesVBOID, std::vector<int> &indices) const;
        void UpdateData(GLuint VBOID, std::vector<float> &data, BufferTypes buffType, int layoutLocation) const;
        void UseVAOEnd() const;
        void CleanupBase() const;

        std::shared_ptr<ShaderProgram> m_shaderProgram;

      private:
        void SetArrayBufferData(GLuint VBOID, int numEntries, const void *data, int numFloatsPerEntry,
                                int layoutLocation = -1) const;
        void SetArrayBufferDataInt(GLuint VBOID, int numEntries, const void *data, int numFloatsPerEntry,
                                   int layoutLocation = -1) const;
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
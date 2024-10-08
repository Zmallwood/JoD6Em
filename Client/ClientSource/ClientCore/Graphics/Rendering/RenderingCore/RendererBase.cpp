/*
 * RendererBase.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RendererBase.hpp"
#include "ShaderProgram.hpp"

namespace JoD {
namespace {
// Predefined constants of number of floats for different entry types.
    const auto k_numFloatsPerEntry
    {std::map<BuffTypes, int> {
         {BuffTypes::Indices, 1},
         {BuffTypes::Pos2D, 2},
         {BuffTypes::Pos3D, 3},
         {BuffTypes::Colors, 4},
         {BuffTypes::UVs, 2},
         {BuffTypes::Normals, 3},
         {BuffTypes::BoneIDs, 4},
         {BuffTypes::Weights, 4}}};
}

RendererBase::RendererBase()
    : m_shaderProgram(std::make_unique<ShaderProgram>()) {}

GLuint RendererBase::GenNewVAOID() {
// Generate new Vertex Array Object.
    GLuint vaoID;
    glGenVertexArraysOES(1, &vaoID);
// Store newly created VAO id and return it.
    m_VAOIDs.push_back(vaoID);
    return vaoID;
}

GLuint RendererBase::GenNewBuffID(
    BuffTypes buffType,
    GLuint vaoID) {
// Generate new Vertex Buffer Object.
    GLuint buffID;
    glGenBuffers(1, &buffID);
// If necessary storing structures not created yet, create them.
    if (!m_VBOIDs.contains(buffType)) {
        m_VBOIDs.insert(
            {buffType, std::map<GLuint, GLuint>()});
    }
// Store newly created VBO id, with the VAO id as one of keys.
    (m_VBOIDs)[buffType][vaoID] = buffID;
// Return ID for newly created Vertex Buffer Object.
    return buffID;
}

void RendererBase::SetIndicesData(
    GLuint indicesVBOID,
    int numIndices,
    const void *data) const {
// Bind the VBO buffer that should hold indices data.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBOID);
// Set indices data as element array buffer.
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        numIndices * k_numFloatsPerEntry.at(BuffTypes::Indices) *
        sizeof(float),
        data,
        GL_DYNAMIC_DRAW);
}

void RendererBase::SetData(
    GLuint VBOID,
    int numEntries,
    const void *data,
    BuffTypes buffType,
    int layoutLocation) const {
    if (buffType == BuffTypes::BoneIDs) {
// Call other method for BoneIDs than other buffer types.
        SetArrayBufferDataInt(
            VBOID,
            numEntries,
            data,
            k_numFloatsPerEntry.at(buffType),
            layoutLocation);
    }
    else {
// Call this function for all buffer types except BoneIDs.
        SetArrayBufferData(
            VBOID,
            numEntries,
            data,
            k_numFloatsPerEntry.at(buffType),
            layoutLocation);
    }
}

void RendererBase::SetArrayBufferData(
    GLuint VBOID,
    int numEntries,
    const void *data,
    int numFloatsPerEntry,
    int layoutLocation) const {
// Bind the VBO for the provided VBO id.
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
// Set the buffer data as an array buffer.
    glBufferData(
        GL_ARRAY_BUFFER,
        numEntries * numFloatsPerEntry * sizeof(float),
        data,
        GL_DYNAMIC_DRAW);
// Is valid layout location?
    if (layoutLocation >= 0){
// Configure layout float float values.
        glVertexAttribPointer(
            layoutLocation,
            numFloatsPerEntry,
            GL_FLOAT,
            GL_FALSE,
            0,
            (const GLvoid *)0);
// Enable layout.
        glEnableVertexAttribArray(layoutLocation);
    }
}

void RendererBase::SetArrayBufferDataInt(
    GLuint VBOID,
    int numEntries,
    const void *data,
    int numFloatsPerEntry,
    int layoutLocation) const {
// Bind the VBO for the provided VBO id.
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
// Set the buffer data as an array buffer.
    glBufferData(
        GL_ARRAY_BUFFER,
        numEntries * numFloatsPerEntry * sizeof(int),
        data,
        GL_DYNAMIC_DRAW);
// Is valid layout location?
    if (layoutLocation >= 0){
// Enable generic vertex attribute.
        glEnableVertexAttribArray(3);
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

GLuint RendererBase::GetUniformLocation(
    std::string_view variableName) const {
// Get layout location of uniform variable in the shader.
    return glGetUniformLocation(
        m_shaderProgram->GetProgramID(),
        variableName.data());
}

void RendererBase::UseVAOBegin(GLuint VAOID, bool useProgram) const {
// Start using shader program and provided VAO.
    if (useProgram)
        glUseProgram(m_shaderProgram->GetProgramID());
    glBindVertexArrayOES(VAOID);
}

GLuint RendererBase::GetBuffID(
    BuffTypes buffType,
    GLuint VAOID) const {
// Returns the buffer of provided type and VAO id.
    return m_VBOIDs.at(buffType).at(VAOID);
}

void RendererBase::UpdIndicesData(
    GLuint indicesVBOID,
    std::vector<int> &indices) const {
// Bind VBO with provided id, being an element array buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBOID);
// Set the buffer data.
    glBufferSubData(
        GL_ELEMENT_ARRAY_BUFFER,
        0,
        sizeof(float) * indices.size(),
        indices.data());
}

void RendererBase::UpdateArrayBufferData(
    GLuint VBOID,
    const std::vector<float> &data,
    int numFloatsPerEntry,
    int layoutLocation) const {
// Bind VBO with provided id, being an array buffer.
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
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
// Enable layout.
    glEnableVertexAttribArray(layoutLocation);
}

void RendererBase::UpdateArrayBufferDataInt(
    GLuint VBOID,
    const std::vector<float> &data,
    int numFloatsPerEntry,
    int layoutLocation) const {
// Bind VBO with provided id, being an array buffer.
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
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
// Enable layout.
    glEnableVertexAttribArray(layoutLocation);
}

void RendererBase::UpdData(
    GLuint VBOID,
    const std::vector<float> &data,
    BuffTypes buffType,
    int layoutLocation) const {
// Does the buffer hold BoneID data?
    if (buffType == BuffTypes::BoneIDs){
// If so, update buffer with int data.
        UpdateArrayBufferDataInt(
            VBOID,
            data,
            k_numFloatsPerEntry.at(buffType),
            layoutLocation);
    }
    else {
// Else, update with float data.
        UpdateArrayBufferData(
            VBOID,
            data,
            k_numFloatsPerEntry.at(buffType),
            layoutLocation);
    }
}

void RendererBase::UseVAOEnd(bool stopUseProgram) const {
// Unbind currently used VAO.
    glBindVertexArrayOES(0);
// Stop using shader program.
    if (stopUseProgram)
        glUseProgram(0);
}

void RendererBase::CleanupBase() const {
// Loop through all keys of buffer types.
    for (const auto &buff_type : m_VBOIDs)
// Loop through all keys of VAO ids.
        for (const auto &buffer_entry : buff_type.second)
// Delete every VBO.
            glDeleteBuffers(1, &buffer_entry.second);
// Loop through all VAO ids.
    for (const auto vao_id : m_VAOIDs)
// And delete them.
        glDeleteVertexArraysOES(1, &vao_id);
// Finally, clean up shader proram.
    m_shaderProgram->Cleanup();
}
}

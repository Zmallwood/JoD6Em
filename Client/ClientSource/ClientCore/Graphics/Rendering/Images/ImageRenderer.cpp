/*
 * ImageRenderer.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ImageRenderer.hpp"
#include "ClientCore/Assets/ImageBank.hpp"
#include "ClientCore/Graphics/Rendering/RenderingCore/ShaderProgram.hpp"
#include "Shader/DefaultShaderImagesFragment.hpp"
#include "Shader/DefaultShaderImagesVertex.hpp"

namespace JoD {
    
    namespace {
        
        int locNoPixelEffect{-1}; // Location of pixelation effect switch variable in vertex shader.
        std::vector<int> defaultIndices;
        const std::vector<float> k_defaultColorsWhite = std::vector<float>(
            16,
            1.0f);                                                                    ///< A set of floats representing the default white image color.
        const std::vector<float> k_defaultUVs ///< A set of floats representing a default UV coordinates layout for an image.
        {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};
        constexpr int k_locPosition{0}; // Location of position variable in vertex shader.
        constexpr int k_locColor{1}; // Location of color variable in vertex shader.
        constexpr int k_locUV{2}; // Location of UV variable in vertex shader.
    }
    
    ImageRenderer::ImageRenderer(){
        
        // Create shader program.
        GetShaderProgram()->Create(
            g_defaultShaderImagesVertex,
            g_defaultShaderImagesFragment);
        
        // m_locNoPixelEffect = GetUniformLocation("noPixelEffect");
        
        // Create indices for the vertices.
        defaultIndices = std::vector<int>(
            MathConstants::k_numVerticesInRectangle);
        std::iota(std::begin(defaultIndices), std::end(defaultIndices), 0);
    }
    
    ImageRenderer::~ImageRenderer(){
        
        // Delete allocated resources for the renderer.
        CleanupBase();
    }
    
    RID ImageRenderer::NewImage() {
        
        // Create new Vertex Array Object.
        const auto rid = GenNewVAOID();
        
        // Use it.
        UseVAOBegin(rid);
        
        // Create buffers that are needed for 2D image rendering.
        const auto indexBuffID = GenNewBuffID(BufferTypes::Indices, rid);
        const auto posBuffID = GenNewBuffID(BufferTypes::Positions2D, rid);
        const auto colorBuffID = GenNewBuffID(BufferTypes::Colors, rid);
        const auto uvBuffID = GenNewBuffID(BufferTypes::UVs, rid);
        
        // Set buffers to empty data.
        SetIndicesData(
            indexBuffID,
            MathConstants::k_numVerticesInRectangle,
            nullptr);
        SetData(
            posBuffID,
            MathConstants::k_numVerticesInRectangle,
            nullptr,
            BufferTypes::Positions2D);
        SetData(
            colorBuffID,
            MathConstants::k_numVerticesInRectangle,
            nullptr,
            BufferTypes::Colors);
        SetData(
            uvBuffID,
            MathConstants::k_numVerticesInRectangle,
            nullptr,
            BufferTypes::UVs);
        
        // Stop using the Vertex Array Object.
        UseVAOEnd();
        
        // Return the ID for the created VAO.
        return rid;
    }
    
    void ImageRenderer::DrawImage(
        RID rid,
        int imageNameHash,
        const BoxF &destination,
        bool repeatTexture,
        SizeF textureFillAmount,
        ColorF color) const {
        
        // Convert destination to GL coordinate system.
        const auto glRect = destination.ToGLBoxF();
        
        // No need for depth testing in a 2D plane.
        glDisable(GL_DEPTH_TEST);
        
        // Obtain GL ID for image to be rendered.
        const auto imageID = _<ImageBank>().GetImage(imageNameHash);
        
        if (imageID == -1) {
            
            // If requested image not found, stop the rendering.
            return;
        }
        
        // Start use the image.
        glBindTexture(GL_TEXTURE_2D, imageID);
        
        // If we should repeat the texture as a pattern or fit it to the destination rectangle.
        if (repeatTexture){
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }else{
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        
        std::vector<float> positions;
        
        positions.push_back(glRect.x);
        positions.push_back(glRect.y - glRect.h);
        positions.push_back(glRect.x);
        positions.push_back(glRect.y);
        positions.push_back(glRect.x + glRect.w);
        positions.push_back(glRect.y);
        positions.push_back(glRect.x + glRect.w);
        positions.push_back(glRect.y - glRect.h);
        
        // Start using the Vertex Array Object.u
        UseVAOBegin(rid);
        
        // If pixelation effect should be used.
        const auto noPixelEffect = true;
        
        // glUniform1f(m_locNoPixelEffect, noPixelEffect ? 1.0f : 0.0f);
        
        // Get buffer IDs for the required data contents.
        const auto indexBuffID = GetBuffID(BufferTypes::Indices, rid);
        const auto posBuffID = GetBuffID(BufferTypes::Positions2D, rid);
        const auto colorBuffID = GetBuffID(BufferTypes::Colors, rid);
        const auto uvBuffID = GetBuffID(BufferTypes::UVs, rid);
        
        // Provide the float vector data to the buffers.
        UpdateIndicesData(indexBuffID, defaultIndices);
        UpdateData(
            posBuffID, positions, BufferTypes::Positions2D,
            k_locPosition);
        
        if (color == Colors::white) {
            
            UpdateData(
                colorBuffID, k_defaultColorsWhite, BufferTypes::Colors,
                k_locColor);
        }else {
            
            std::vector<float> colors;
            
            for (auto i = 0; i < 4; i++) {
                
                colors.push_back(color.r);
                colors.push_back(color.g);
                colors.push_back(color.b);
                colors.push_back(color.a);
            }
            
            UpdateData(
                colorBuffID, colors, BufferTypes::Colors,
                k_locColor);
        }
        if (textureFillAmount.w == 1.0f && textureFillAmount.h == 1.0f) {
            
            UpdateData(uvBuffID, k_defaultUVs, BufferTypes::UVs, k_locUV);
        } else {
            
            std::vector<float> uvs;
            
            uvs.push_back(0.0f);
            uvs.push_back(1.0f / textureFillAmount.h);
            uvs.push_back(0.0f);
            uvs.push_back(0.0f);
            uvs.push_back(1.0f / textureFillAmount.w);
            uvs.push_back(0.0f);
            uvs.push_back(1.0f / textureFillAmount.w);
            uvs.push_back(1.0f / textureFillAmount.h);
            
            UpdateData(uvBuffID, uvs, BufferTypes::UVs, k_locUV);
        }
        
        // Do the actual rendering.
        glDrawElements(
            GL_TRIANGLE_FAN,
            MathConstants::k_numVerticesInRectangle, GL_UNSIGNED_INT, NULL);
        
        // Stop using the Vertex Array Object.
        UseVAOEnd();
    }
    
    void ImageRenderer::DrawImage(
        RID rid,
        std::string_view imageName,
        const BoxF &destination,
        bool repeatTexture,
        SizeF textureFillAmount,
        ColorF color) const {
        
        // Forward the method call to the main overload.
        DrawImage(
            rid, Hash(imageName), destination, repeatTexture,
            textureFillAmount, color);
    }
}
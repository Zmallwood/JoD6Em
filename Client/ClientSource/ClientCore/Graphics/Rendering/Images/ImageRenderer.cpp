/*
 * ImageRenderer.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ImageRenderer.hpp"
#include "ClientCore/Assets/ImageBank.hpp"
#include "ClientCore/Graphics/Rendering/RenderingCore/ShaderProgram.hpp"
#include "Shader/DefaultShaderImagesFragment.hpp"
#include "Shader/DefaultShaderImagesVertex.hpp"

namespace JoD {
namespace {
    int locNoPixelEffect {-1};
    std::vector<int> defaultIndices;
    const std::vector<float> k_defaultColorsWhite
        =  std::vector<float>(
              16,
              1.0f);
    const std::vector<float> k_defaultUVs
    {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};
    constexpr int k_locPosition {0};
    constexpr int k_locColor {1};
    constexpr int k_locUV {2};
}

ImageRenderer::ImageRenderer() {
    GetShaderProgram()->Create(
        g_defaultShaderImagesVertex,
        g_defaultShaderImagesFragment);
    defaultIndices = std::vector<int>(
        MathConstants::k_numVerticesInRectangle);
    std::iota(std::begin(defaultIndices), std::end(defaultIndices), 0);
}

ImageRenderer::~ImageRenderer() {
    CleanupBase();
}

RID ImageRenderer::NewImage() {
    const auto rid = GenNewVAOID();
    UseVAOBegin(rid);
    const auto indexBuffID = GenNewBuffID(BufferTypes::Indices, rid);
    const auto posBuffID = GenNewBuffID(BufferTypes::Positions2D, rid);
    const auto colorBuffID = GenNewBuffID(BufferTypes::Colors, rid);
    const auto uvBuffID = GenNewBuffID(BufferTypes::UVs, rid);
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
    UpdateIndicesData(indexBuffID, defaultIndices);
    UpdateData(
        colorBuffID, k_defaultColorsWhite, BufferTypes::Colors,
        k_locColor);
    UpdateData(uvBuffID, k_defaultUVs, BufferTypes::UVs, k_locUV);
    UseVAOEnd();
    return rid;
}

void ImageRenderer::DrawImage(
    RID rid,
    int imageNameHash,
    const BoxF &destination,
    bool repeatTexture,
    SizeF textureFillAmount,
    ColorF color) const {
    const auto glRect = destination.ToGLBoxF();
    glDisable(GL_DEPTH_TEST);
    const auto imageID = _<ImageBank>().GetImage(imageNameHash);
    if (imageID == std::nullopt)
        return;
    glBindTexture(GL_TEXTURE_2D, imageID.value());
    if (repeatTexture){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else{
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
    UseVAOBegin(rid);
    auto noPixelEffect = true;
    GLuint colorBuffID;
    GLuint uvBuffID;
    auto posBuffID = GetBuffID(BufferTypes::Positions2D, rid);
    UpdateData(
        posBuffID, positions, BufferTypes::Positions2D,
        k_locPosition);
    if (color != Colors::white) {
        colorBuffID = GetBuffID(BufferTypes::Colors, rid);
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
    if (textureFillAmount.w != 1.0f || textureFillAmount.h != 1.0f) {
        uvBuffID = GetBuffID(BufferTypes::UVs, rid);
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
    glDrawElements(
        GL_TRIANGLE_FAN,
        MathConstants::k_numVerticesInRectangle, GL_UNSIGNED_INT, NULL);
    if (color != Colors::white) {
        UpdateData(
            colorBuffID, k_defaultColorsWhite, BufferTypes::Colors,
            k_locColor);
    }
    if (textureFillAmount.w != 1.0f || textureFillAmount.h != 1.0f) {
        UpdateData(uvBuffID, k_defaultUVs, BufferTypes::UVs, k_locUV);
    }
    UseVAOEnd();
}

void ImageRenderer::DrawImage(
    RID rid,
    std::string_view imageName,
    const BoxF &destination,
    bool repeatTexture,
    SizeF textureFillAmount,
    ColorF color) const {
    DrawImage(
        rid, Hash(imageName), destination, repeatTexture,
        textureFillAmount, color);
}
}

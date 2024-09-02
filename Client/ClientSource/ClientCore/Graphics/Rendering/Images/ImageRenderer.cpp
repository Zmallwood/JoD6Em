/*
 * ImageRenderer.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ImageRenderer.hpp"
#include "ClientCore/Assets/ImageBank.hpp"
#include "ClientCore/Graphics/Rendering/RenderingCore/ShaderProgram.hpp"
#include "Shader/ShaderImagesFrag.hpp"
#include "Shader/ShaderImagesVert.hpp"

namespace JoD {

namespace {
    
    int locNoPixelFX {-1};
    auto defaultIndices {std::vector<int>(MathConsts::k_numVertsInRect)};
    const auto k_defaultClrWhite {std::vector<float>(16, 1.0f)};
    const std::vector<float> k_defaultUVs {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                           1.0f, 1.0f};
    constexpr int k_locPos {0};
    constexpr int k_locColor {1};
    constexpr int k_locUV {2};
}

ImageRenderer::ImageRenderer() {
    
    GetShaderProg()->Create(g_shaderImagesVert, g_shaderImagesFrag);
    
    std::iota(std::begin(defaultIndices), std::end(defaultIndices), 0);
}

ImageRenderer::~ImageRenderer() {
    
    CleanupBase();
}

RID ImageRenderer::NewImg() {
    
    auto rid = GenNewVAOID();
    
    UseVAOBegin(rid);
    
    auto indexBuffID = GenNewBuffID(BuffTypes::Indices, rid);
    auto posBuffID = GenNewBuffID(BuffTypes::Pos2D, rid);
    auto colorBuffID = GenNewBuffID(BuffTypes::Colors, rid);
    auto uvBuffID = GenNewBuffID(BuffTypes::UVs, rid);
    
    SetIndicesData(indexBuffID, MathConsts::k_numVertsInRect, nullptr);
    SetData(posBuffID, MathConsts::k_numVertsInRect, nullptr, BuffTypes::Pos2D);
    SetData(
        colorBuffID, MathConsts::k_numVertsInRect, nullptr,
        BuffTypes::Colors);
    SetData(uvBuffID, MathConsts::k_numVertsInRect, nullptr, BuffTypes::UVs);
    
    UpdIndicesData(indexBuffID, defaultIndices);
    UpdData(colorBuffID, k_defaultClrWhite, BuffTypes::Colors, k_locColor);
    UpdData(uvBuffID, k_defaultUVs, BuffTypes::UVs, k_locUV);
    
    UseVAOEnd(false);
    
    return rid;
}

void ImageRenderer::DrawImg(
    RID rid,
    int imgNameHash,
    const BoxF &dest,
    bool repeatTex,
    SizeF texFillAmount,
    ColorF color) const {
    
    auto glRect = dest.ToGLBoxF();
    
    glDisable(GL_DEPTH_TEST);
    
    auto imgID = _<ImageBank>().GetImage(imgNameHash);
    
    if (imgID == std::nullopt) return;
    
    glBindTexture(GL_TEXTURE_2D, imgID.value());
    
    if (repeatTex) {
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else {
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    
    std::vector<float> posData;
    
    posData.push_back(glRect.x);
    posData.push_back(glRect.y - glRect.h);
    posData.push_back(glRect.x);
    posData.push_back(glRect.y);
    posData.push_back(glRect.x + glRect.w);
    posData.push_back(glRect.y);
    posData.push_back(glRect.x + glRect.w);
    posData.push_back(glRect.y - glRect.h);
    
    UseVAOBegin(rid, false);
    
    auto noPixelFX = true;
    GLuint colorBuffID;
    GLuint uvBuffID;
    
    auto posBuffID = GetBuffID(BuffTypes::Pos2D, rid);
    
    UpdData(posBuffID, posData, BuffTypes::Pos2D, k_locPos);
    
    if (color != Colors::white) {
        
        colorBuffID = GetBuffID(BuffTypes::Colors, rid);
        
        std::vector<float> colors;
        
        for (auto i = 0; i < 4; i++) {
            
            colors.push_back(color.r);
            colors.push_back(color.g);
            colors.push_back(color.b);
            colors.push_back(color.a);
        }
        
        UpdData(colorBuffID, colors, BuffTypes::Colors, k_locColor);
    }
    if (texFillAmount.w != 1.0f || texFillAmount.h != 1.0f) {
        
        uvBuffID = GetBuffID(BuffTypes::UVs, rid);
        
        std::vector<float> uvs;
        
        uvs.push_back(0.0f);
        uvs.push_back(1.0f / texFillAmount.h);
        uvs.push_back(0.0f);
        uvs.push_back(0.0f);
        uvs.push_back(1.0f / texFillAmount.w);
        uvs.push_back(0.0f);
        uvs.push_back(1.0f / texFillAmount.w);
        uvs.push_back(1.0f / texFillAmount.h);
        
        UpdData(uvBuffID, uvs, BuffTypes::UVs, k_locUV);
    }
    
    glDrawElements(
        GL_TRIANGLE_FAN, MathConsts::k_numVertsInRect,
        GL_UNSIGNED_INT, nullptr);
    
    if (color != Colors::white)
        UpdData(colorBuffID, k_defaultClrWhite, BuffTypes::Colors, k_locColor);
    
    if (texFillAmount.w != 1.0f || texFillAmount.h != 1.0f)
        UpdData(uvBuffID, k_defaultUVs, BuffTypes::UVs, k_locUV);
    
    UseVAOEnd(false);
}

void ImageRenderer::DrawImg(
    RID rid,
    std::string_view imgName,
    const BoxF &dest,
    bool repeatTex,
    SizeF texFillAmount,
    ColorF color) const {
    
    DrawImg(rid, Hash(imgName), dest, repeatTex, texFillAmount, color);
}
}

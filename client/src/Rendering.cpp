// Copyright (c) 2024 Andreas Åkerberg.

#include "Rendering.h"
#include "Assets.h"

namespace jod
{
    ImageRenderer::ImageRenderer()
    {
        m_shaderProgram->Create(defaultShaderImagesVertex, defaultShaderImagesFragment);
        // m_locNoPixelEffect = GetUniformLocation("noPixelEffect");
    }

    ImageRenderer::~ImageRenderer()
    {
        CleanupBase();
    }

    RID ImageRenderer::NewImage()
    {
        auto rid = GenNewVAOID();
        UseVAOBegin(rid);
        auto indexBuffID = GenNewBuffID(BufferTypes::Indices, rid);
        auto posBuffID = GenNewBuffID(BufferTypes::Positions2D, rid);
        auto colorBuffID = GenNewBuffID(BufferTypes::Colors, rid);
        auto uvBuffID = GenNewBuffID(BufferTypes::UVs, rid);
        SetIndicesData(indexBuffID, RendererBase::NumVerticesInRectangle(), nullptr);
        SetData(posBuffID, RendererBase::NumVerticesInRectangle(), nullptr, BufferTypes::Positions2D);
        SetData(colorBuffID, RendererBase::NumVerticesInRectangle(), nullptr, BufferTypes::Colors);
        SetData(uvBuffID, RendererBase::NumVerticesInRectangle(), nullptr, BufferTypes::UVs);
        UseVAOEnd();

        return rid;
    }

    void ImageRenderer::DrawImage(RID rid, int imageNameHash, const RectF &dest, bool repeatTexture,
                                  SizeF textureFillAmount, ColorF color)
    {
        auto GLRect = dest.ToGLRectF();

        Vertex2F verts[RendererBase::NumVerticesInRectangle()];
        verts[0].pos = {GLRect.x, GLRect.y - GLRect.h};
        verts[1].pos = {GLRect.x, GLRect.y};
        verts[2].pos = {GLRect.x + GLRect.w, GLRect.y};
        verts[3].pos = {GLRect.x + GLRect.w, GLRect.y - GLRect.h};
        verts[0].uv = {0.0f, 1.0f / textureFillAmount.h};
        verts[1].uv = {0.0f, 0.0f};
        verts[2].uv = {1.0f / textureFillAmount.w, 0.0f};
        verts[3].uv = {1.0f / textureFillAmount.w, 1.0f / textureFillAmount.h};
        glDisable(GL_DEPTH_TEST);
        
        auto imageID = _<ImageBank>().GetImage(imageNameHash);

        if (imageID == -1)
            return;

        glBindTexture(GL_TEXTURE_2D, imageID);

        if (repeatTexture)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        auto indices = std::vector<int>(RendererBase::NumVerticesInRectangle());
        std::iota(std::begin(indices), std::end(indices), 0);
        std::vector<float> positions;
        std::vector<float> colors;
        std::vector<float> uvs;

        for (auto &vert : verts)
        {
            positions.push_back(vert.pos.x);
            positions.push_back(vert.pos.y);
            colors.push_back(color.r);
            colors.push_back(color.g);
            colors.push_back(color.b);
            colors.push_back(color.a);
            uvs.push_back(vert.uv.x);
            uvs.push_back(vert.uv.y);
        }

        UseVAOBegin(rid);
        auto noPixelEffect = true;
        // glUniform1f(m_locNoPixelEffect, noPixelEffect ? 1.0f : 0.0f);
        auto indexBuffID = GetBuffID(BufferTypes::Indices, rid);
        auto posBuffID = GetBuffID(BufferTypes::Positions2D, rid);
        auto colorBuffID = GetBuffID(BufferTypes::Colors, rid);
        auto uvBuffID = GetBuffID(BufferTypes::UVs, rid);
        UpdateIndicesData(indexBuffID, indices);
        UpdateData(posBuffID, positions, BufferTypes::Positions2D, k_locPosition);
        UpdateData(colorBuffID, colors, BufferTypes::Colors, k_locColor);
        UpdateData(uvBuffID, uvs, BufferTypes::UVs, k_locUv);
        glDrawElements(GL_TRIANGLE_FAN, RendererBase::NumVerticesInRectangle(), GL_UNSIGNED_INT, NULL);
        UseVAOEnd();
    }

    void ImageRenderer::DrawImage(RID rid, std::string_view imageName, const RectF &dest, bool repeatTexture,
                                  SizeF textureFillAmount, ColorF color)
    {
        DrawImage(rid, Hash(imageName), dest, repeatTexture, textureFillAmount, color);
    }
}
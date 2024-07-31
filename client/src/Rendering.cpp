// Copyright (c) 2024 Andreas Åkerberg.

#include "Rendering.h"

#include "Assets.h"

namespace jod
{
    namespace
    {
        /* Shader sources */

        // clang-format off
    const GLchar *defaultShaderImagesVertex =
      "#version 300 es\n"
      "layout (location = 0) in vec3 aPos;\n"
      "layout (location = 1) in vec4 in_Color;\n"
      "layout (location = 2) in vec2 in_TexCoord;\n"
      "out vec4 ex_Color;\n"
      "out vec2 ex_TexCoord;\n"
      "out vec2 ex_Pos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "   ex_Color = in_Color;\n"
      "   ex_TexCoord = in_TexCoord;\n"
      "   ex_Pos = aPos.xy;\n"
      "}\0";

    const GLchar *defaultShaderImagesFragment =
      "#version 300 es\n"
      "precision mediump float;\n"
      "in vec4 ex_Color;\n"
      "in vec2 ex_TexCoord;\n"
      "in vec2 ex_Pos;\n"
      "out vec4 FragColor;\n"
      "uniform sampler2D TexUnit;\n"
      "void main() {\n"
      "    FragColor = texture(TexUnit, ex_TexCoord);\n"
      "}\0";
        // clang-format on

        /* Location of position variable in vertex shader. */
        constexpr int k_locPosition{0};

        /* Location of color variable in vertex shader. */
        constexpr int k_locColor{1};

        /* Location of UV variable in vertex shader. */
        constexpr int k_locUv{2};

        /* Location of pixelation effect switch variable in vertex shader. */
        int m_locNoPixelEffect{-1};
    }

    ImageRenderer::ImageRenderer()
    {
        /* Create shader program. */

        m_shaderProgram->Create(defaultShaderImagesVertex, defaultShaderImagesFragment);

        // m_locNoPixelEffect = GetUniformLocation("noPixelEffect");
    }

    ImageRenderer::~ImageRenderer()
    {
        /* Delete allocated resources for the renderer. */

        CleanupBase();
    }

    RID ImageRenderer::NewImage()
    {
        /* Create new Vertex Array Object. */

        auto rid = GenNewVAOID();

        /* Use it. */

        UseVAOBegin(rid);

        /* Create buffers that are needed for 2D image rendering. */

        auto indexBuffID = GenNewBuffID(BufferTypes::Indices, rid);
        auto posBuffID = GenNewBuffID(BufferTypes::Positions2D, rid);
        auto colorBuffID = GenNewBuffID(BufferTypes::Colors, rid);
        auto uvBuffID = GenNewBuffID(BufferTypes::UVs, rid);

        /* Set buffers to empty data. */

        SetIndicesData(indexBuffID, MathConstants::k_numVerticesInRectangle, nullptr);
        SetData(posBuffID, MathConstants::k_numVerticesInRectangle, nullptr,
                BufferTypes::Positions2D);
        SetData(colorBuffID, MathConstants::k_numVerticesInRectangle, nullptr, BufferTypes::Colors);
        SetData(uvBuffID, MathConstants::k_numVerticesInRectangle, nullptr, BufferTypes::UVs);

        /* Stop using the Vertex Array Object. */

        UseVAOEnd();

        /* Return the ID for the created VAO. */

        return rid;
    }

    void ImageRenderer::DrawImage(RID rid, int imageNameHash, const RectF &dest, bool repeatTexture,
                                  SizeF textureFillAmount, ColorF color)
    {
        /* Convert destination to GL coordinate system. */

        auto GLRect = dest.ToGLRectF();

        /* Create 4 vertices for an image rectangle. */

        Vertex2F verts[MathConstants::k_numVerticesInRectangle];

        /* Set vertices positions. */

        verts[0].pos = {GLRect.x, GLRect.y - GLRect.h};
        verts[1].pos = {GLRect.x, GLRect.y};
        verts[2].pos = {GLRect.x + GLRect.w, GLRect.y};
        verts[3].pos = {GLRect.x + GLRect.w, GLRect.y - GLRect.h};

        /* Set vertices UVs (texture coordinates). */

        verts[0].uv = {0.0f, 1.0f / textureFillAmount.h};
        verts[1].uv = {0.0f, 0.0f};
        verts[2].uv = {1.0f / textureFillAmount.w, 0.0f};
        verts[3].uv = {1.0f / textureFillAmount.w, 1.0f / textureFillAmount.h};

        /* No need for depth testing in a 2D plane. */

        glDisable(GL_DEPTH_TEST);

        /* Obtain GL ID for image to be rendered. */

        auto imageID = _<ImageBank>().GetImage(imageNameHash);

        /* If requested image not found, stop the rendering. */

        if (imageID == -1)
            return;

        /* Start use the image. */

        glBindTexture(GL_TEXTURE_2D, imageID);

        /* If we should repeat the texture as a pattern or fit it to the destination rectangle. */

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

        /* Create indices for the vertices. */

        auto indices = std::vector<int>(MathConstants::k_numVerticesInRectangle);
        std::iota(std::begin(indices), std::end(indices), 0);

        /* Put render input into pure float vector format. */

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

        /* Start using the Vertex Array Object. */

        UseVAOBegin(rid);

        /* If pixelation effect should be used. */

        auto noPixelEffect = true;
        // glUniform1f(m_locNoPixelEffect, noPixelEffect ? 1.0f : 0.0f);

        /* Get buffer IDs for the required data contents. */

        auto indexBuffID = GetBuffID(BufferTypes::Indices, rid);
        auto posBuffID = GetBuffID(BufferTypes::Positions2D, rid);
        auto colorBuffID = GetBuffID(BufferTypes::Colors, rid);
        auto uvBuffID = GetBuffID(BufferTypes::UVs, rid);

        /* Provide the float vector data to the buffers. */

        UpdateIndicesData(indexBuffID, indices);
        UpdateData(posBuffID, positions, BufferTypes::Positions2D, k_locPosition);
        UpdateData(colorBuffID, colors, BufferTypes::Colors, k_locColor);
        UpdateData(uvBuffID, uvs, BufferTypes::UVs, k_locUv);

        /* Do the actual rendering. */

        glDrawElements(GL_TRIANGLE_FAN, MathConstants::k_numVerticesInRectangle, GL_UNSIGNED_INT,
                       NULL);

        /* Stop using the Vertex Array Object. */

        UseVAOEnd();
    }

    void ImageRenderer::DrawImage(RID rid, std::string_view imageName, const RectF &dest,
                                  bool repeatTexture, SizeF textureFillAmount, ColorF color)
    {
        /* Forward the method call to the main overload. */

        DrawImage(rid, Hash(imageName), dest, repeatTexture, textureFillAmount, color);
    }
}
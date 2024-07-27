#pragma once

#include "RenderingCore.h"

namespace jod
{
    inline static const GLchar *defaultShaderImagesVertex = "#version 300 es\n"
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

    inline static const GLchar *defaultShaderImagesFragment = "#version 300 es\n"
                                                              "precision mediump float;\n"
                                                              "in vec4 ex_Color;\n"
                                                              "in vec2 ex_TexCoord;\n"
                                                              "in vec2 ex_Pos;\n"
                                                              "out vec4 FragColor;\n"
                                                              "uniform sampler2D TexUnit;\n"
                                                              "void main() {\n"
                                                              "    FragColor = texture(TexUnit, ex_TexCoord);\n"
                                                              "}\0";

    class ImageRenderer : public RendererBase
    {
      public:
        ImageRenderer();
        ~ImageRenderer();
        RID NewImage();
        void DrawImage(RID rid, std::string_view imageName, const RectF &dest, bool repeatTexture = false,
                       SizeF textureFillAmount = {1.0f, 1.0f}, ColorF color = {1.0f, 1.0f, 1.0f});
        void DrawImage(RID rid, int imageNameHash, const RectF &dest, bool repeatTexture = false,
                       SizeF textureFillAmount = {1.0f, 1.0f}, ColorF color = {1.0f, 1.0f, 1.0f});

      private:
        static constexpr int k_locPosition{0};
        static constexpr int k_locColor{1};
        static constexpr int k_locUv{2};
        int m_locNoPixelEffect{-1};
    };
}
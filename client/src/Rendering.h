// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

#include "RenderingCore.h"

namespace jod
{
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
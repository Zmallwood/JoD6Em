/*
 * ImageRenderer.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "ClientCore/Graphics/Rendering/RenderingCore/RendererBase.hpp"

namespace JoD {
class ImageRenderer : public RendererBase {
  public:
    ImageRenderer();
    ~ImageRenderer();
    RID NewImage();
    void DrawImage(
        RID rid,
        std::string_view imageName,
        const BoxF &destination,
        bool repeatTexture = false,
        SizeF textureFillAmount = {1.0f, 1.0f},
        ColorF color = Colors::white) const;
    void DrawImage(
        RID rid,
        int imageNameHash,
        const BoxF &destination,
        bool repeatTexture = false,
        SizeF textureFillAmount = {1.0f, 1.0f},
        ColorF color = Colors::white) const;
};
}

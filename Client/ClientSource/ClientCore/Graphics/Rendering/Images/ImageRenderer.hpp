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
    RID NewImg();
    void DrawImg(RID rid, std::string_view imgName, const BoxF &dest,
                 bool repeatTex = false, SizeF texFillAmount = {1.0f, 1.0f},
                 ColorF color = Colors::white) const;
    void DrawImg(RID rid, int imgNameHash, const BoxF &dest,
                 bool repeatTex = false, SizeF texFillAmount = {1.0f, 1.0f},
                 ColorF color = Colors::white) const;
};
}

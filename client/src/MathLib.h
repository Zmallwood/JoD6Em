// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
    namespace MathConstants
    {
        inline static constexpr int k_numVerticesInRectangle = 4;
    }

    class PointF
    {
      public:
        float x = 0.0f;
        float y = 0.0f;
    };

    class SizeF
    {
      public:
        float w = 0.0f;
        float h = 0.0f;
    };

    class GLRectF
    {
      public:
        float x = 0.0f;
        float y = 0.0f;
        float w = 0.0f;
        float h = 0.0f;
    };

    class RectF
    {
      public:
        GLRectF ToGLRectF() const;

        float x = 0.0f;
        float y = 0.0f;
        float w = 0.0f;
        float h = 0.0f;
    };

    class ColorF
    {
      public:
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 1.0f;
    };

    class Vertex2F
    {
      public:
        PointF pos;
        ColorF color;
        PointF uv;
    };
}
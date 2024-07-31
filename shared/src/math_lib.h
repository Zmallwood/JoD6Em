// Copyright (c) 2024 Andreas Åkerberg.
#pragma once
namespace jod {
    namespace math_constants {
        inline static constexpr int k_numVerticesInRectangle = 4; ///< To avoid magic number.
    }
    struct Point {
        int x = 0;
        int y = 0;
    };
    /////////////////////////////////////////////////
    /// \brief Point with float coordinates.
    /////////////////////////////////////////////////
    struct PointF {
        float x = 0.0f; ///< X coordinate in float type.
        float y = 0.0f; ///< Y coordinate in float type.
    };
    /////////////////////////////////////////////////
    /// \brief Size with int dimension.
    ///
    /////////////////////////////////////////////////
    struct Size {
        int w = 0; ///< Width in int type.
        int h = 0; ///< Height in int type.
    };
    /////////////////////////////////////////////////
    /// \brief Size with float dimension.
    ///
    /////////////////////////////////////////////////
    struct SizeF {
        float w = 0.0f; ///< Width in float type.
        float h = 0.0f; ///< Height in float type.
    };
    /////////////////////////////////////////////////
    /// \brief Rectangle object with float dimensions, ment to represent a rectangle for OpenGLs
    ///        default coordinate system.
    /////////////////////////////////////////////////
    struct GLRectF {
        float x = 0.0f; ///< X coordinate in float type.
        float y = 0.0f; ///< Y coordinate in float type.
        float w = 0.0f; ///< Width in float type.
        float h = 0.0f; ///< Height in float type.
    };
    /////////////////////////////////////////////////
    /// \brief Rectangle object with float dimensions, ment to represent a rectangle in standard
    ///        screen coordinates, with 0,0 being in top left corner and 1,1 being in bottom right
    ///        corner.
    /////////////////////////////////////////////////
    struct RectF {
        /////////////////////////////////////////////////
        /// \brief Convert this objects values to format of OpenGLs default coordinate system.
        /// \return GLRectF Converted resulting object.
        /////////////////////////////////////////////////
        GLRectF ToGLRectF() const;
        
        float x = 0.0f; ///< X coordinate in float type.
        float y = 0.0f; ///< Y coordinate in float type.
        float w = 0.0f; ///< Width in float type.
        float h = 0.0f; ///< Height in float type.
    };
    /////////////////////////////////////////////////
    /// \brief RGBA color object with color components in float type.
    /////////////////////////////////////////////////
    struct ColorF {
        float r = 0.0f; ///< Red component in float type in range 0.0 - 1.0.
        float g = 0.0f; ///< Green component in float type in range 0.0 - 1.0.
        float b = 0.0f; ///< Blue component in float type in range 0.0 - 1.0.
        float a = 1.0f; ///< Alpha component in float type in range 0.0 - 1.0.
    };
    /////////////////////////////////////////////////
    /// \brief Vertex object with position, color and UV data.
    /////////////////////////////////////////////////
    struct Vertex2F {
        PointF pos; ///< Position of this vertex with coordinates in float type.
        ColorF color; ///< Color of this vertex.
        PointF uv; ///< UV coordinates of this vertex.
    };
}
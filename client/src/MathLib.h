// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
    namespace MathConstants
    {
        /**
         * @brief To avoid magic number.
         *
         */
        inline static constexpr int k_numVerticesInRectangle = 4;
    }

    /**
     * @brief Point with float coordinates.
     *
     */
    struct PointF
    {
        /**
         * @brief X coordinate in float type.
         *
         */
        float x = 0.0f;

        /**
         * @brief Y coordinatae in float type.
         *
         */
        float y = 0.0f;
    };

    /**
     * @brief Size with int dimenstion.
     *
     */
    struct Size
    {
        /**
         * @brief Width in int type.
         *
         */
        int w = 0;

        /**
         * @brief Height in int type.
         *
         */
        int h = 0;
    };

    /**
     * @brief Size with float dimenstion.
     *
     */
    struct SizeF
    {
        /**
         * @brief Width in float type.
         *
         */
        float w = 0.0f;

        /**
         * @brief Height in float type.
         *
         */
        float h = 0.0f;
    };

    /**
     * @brief Rectangle object with float dimensions, ment to represent a rectangle for OpenGLs
     *        default coordinate system.
     *
     */
    struct GLRectF
    {
        /**
         * @brief X coordinate in float type.
         *
         */
        float x = 0.0f;

        /**
         * @brief Y coordinate in float type.
         *
         */
        float y = 0.0f;

        /**
         * @brief Width in float type.
         *
         */
        float w = 0.0f;

        /**
         * @brief Height in float type.
         *
         */
        float h = 0.0f;
    };

    /**
     * @brief Rectangle object with float dimensions, ment to represent a rectangle in standard
     *        screen coordinates, with 0,0 being in top left corner and 1,1 being in bottom right
     *        corner.
     *
     */
    struct RectF
    {
        /**
         * @brief Convert this objects values to format of OpenGLs default coordinate system.
         *
         * @return GLRectF Converted resulting object.
         */
        GLRectF ToGLRectF() const;

        /**
         * @brief X coordinate in float type.
         *
         */
        float x = 0.0f;

        /**
         * @brief Y coordinate in float type.
         *
         */
        float y = 0.0f;

        /**
         * @brief Width in float type.
         *
         */
        float w = 0.0f;

        /**
         * @brief Height in float type.
         *
         */
        float h = 0.0f;
    };

    /**
     * @brief RGBA color object with color components in float type.
     *
     */
    struct ColorF
    {
        /**
         * @brief Red component in float type in range 0.0 - 1.0.
         *
         */
        float r = 0.0f;

        /**
         * @brief Green component in float type in range 0.0 - 1.0.
         *
         */
        float g = 0.0f;

        /**
         * @brief Blue component in float type in range 0.0 - 1.0.
         *
         */
        float b = 0.0f;

        /**
         * @brief Alpha component in float type in range 0.0 - 1.0.
         *
         */
        float a = 1.0f;
    };

    /**
     * @brief Vertex object with position, color and UV data.
     *
     */
    struct Vertex2F
    {
        /**
         * @brief Position of this vertex with coordinates in float type.
         *
         */
        PointF pos;

        /**
         * @brief  Color of this vertex.
         *
         */
        ColorF color;

        /**
         * @brief UV coordinates of this vertex.
         *
         */
        PointF uv;
    };
}
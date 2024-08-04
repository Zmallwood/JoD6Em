/*
 * BufferTypes.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    /// @brief Available types of GL buffers that can be created.
    enum class BufferTypes {
        indices, ///< Indices
        positions_2d, ///< Positions in 2D coordinates
        positions_3d, ///< Positions in 3D coordinates.
        colors, ///< Colors.
        uvs, ///< Texture coordinates.
        normals, ///< Normals in 3D space.
        bone_ids, ///< Bone IDs for skeleton animations.
        weights, ///< Bone weights for skeleton animations.
        misc ///< Other types of buffer data.
    };
}
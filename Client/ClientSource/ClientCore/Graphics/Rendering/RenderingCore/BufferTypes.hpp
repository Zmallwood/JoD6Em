/*
 * BufferTypes.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Available types of GL buffers that can be created.
///
enum class BufferTypes {
    
    Indices,         ///< Indices
    Positions2D,     ///< Positions in 2D coordinates
    Positions3D,     ///< Positions in 3D coordinates.
    Colors,          ///< Colors.
    UVs,             ///< Texture coordinates.
    Normals,         ///< Normals in 3D space.
    BoneIDs,         ///< Bone IDs for skeleton animations.
    Weights,         ///< Bone weights for skeleton animations.
    Misc             ///< Other types of buffer data.
};

}
// buffer_types.h

// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>

#pragma once

namespace jod {
    //! \brief Available types of GL buffers that can be created.
    enum class buffer_types {
        Indices,
        Positions2D,
        Positions3D,
        Colors,
        UVs,
        Normals,
        BoneIDs,
        Weights,
        Misc
    };
}
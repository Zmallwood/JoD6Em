/*
 * buffer_types.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    //! \brief Available types of GL buffers that can be created.
    enum class buffer_types {
        indices,
        positions_2d,
        positions_3d,
        colors,
        uvs,
        normals,
        bone_ids,
        weights,
        misc
    };
}
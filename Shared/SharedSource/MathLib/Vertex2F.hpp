/*
 * Vertex2F.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "PointF.hpp"
#include "ColorF.hpp"

namespace JoD {
    
    ///
    /// Vertex object with position, color and UV data.
    ///
    struct Vertex2F {
        
        PointF pos; ///< Position of this vertex with coordinates in float type.
        
        ColorF color; ///< Color of this vertex.
        
        PointF uv; ///< UV coordinates of this vertex.
    };
}
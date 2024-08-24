/*
 * BoxF.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
class PointF;
class GLBoxF;
class SizeF;

/// Rectangle object with float dimensions, ment to represent a rectangle in standard
/// screen coordinates, with 0,0 being in top left corner and 1,1 being in bottom right
/// corner.
struct BoxF {
    /// Convert this objects values to format of OpenGLs default coordinate system.
    /// @return GLRectF Converted resulting object.
    GLBoxF ToGLBoxF() const;
    
/// Get position component of object.
/// @return PointF Position.
    PointF GetPosition() const;
    
/// Get size component of object.
/// @return SizeF Size.
    SizeF GetSize() const;
    
/// Determines if point is inside box bounds.
/// @param point Point to check for.
/// @return bool True if point inside bounds, else false.
    bool Contains(PointF point) const;
    
/// Gets center point of box.
/// @return PointF Center point.
    PointF GetCenter() const;
    
/// X coordinate in float type.
    float x {0.0f};
/// Y coordinate in float type.
    float y {0.0f};
/// Width in float type.
    float w {0.0f};
/// Height in float type.
    float h {0.0f};
};
}

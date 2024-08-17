/*
 * BoxF.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class PointF;
class GLBoxF;
class SizeF;

///
/// Rectangle object with float dimensions, ment to represent a rectangle in standard
/// screen coordinates, with 0,0 being in top left corner and 1,1 being in bottom right
/// corner.
///
struct BoxF {
    ///
    /// Convert this objects values to format of OpenGLs default coordinate system.
    ///
    /// @return GLRectF Converted resulting object.
    ///
    GLBoxF ToGLBoxF() const;
    
    PointF GetPosition() const;
    
    SizeF GetSize() const;
    
    bool Contains(PointF point) const;
    
    PointF GetCenter() const;
    
    // Members
    
    float x {0.0f};     ///< X coordinate in float type.
    
    float y {0.0f};     ///< Y coordinate in float type.
    
    float w {0.0f};     ///< Width in float type.
    
    float h {0.0f};     ///< Height in float type.
};

}

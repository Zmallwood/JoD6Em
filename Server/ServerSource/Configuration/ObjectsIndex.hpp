/*
 * ObjectsIndex.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
/// Manages properties and configuration for object types.
class ObjectsIndex {
  public:
    /// Construct a new Objects Index object by setting up object properties
    /// such as object flags.
    ObjectsIndex();
    
    /// Tells if object of provided type allows walking through them.
    /// @param objectNameHash Hash code of objects name.
    /// @return true If can walk through objects of this type.
    /// @return false If cannot walk through (obstacle) objects of this type.
    bool CanWalkThroughObject(int objectNameHash) const;
    
  private:
// Storage of object types and their flags.
    std::map<int, int> m_objectFlags;
};
}

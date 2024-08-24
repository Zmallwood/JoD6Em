/*
 * ObjectEntry.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
/// An entry with object specifications in ObjectsIndex.
struct ObjectEntry {
/// Name of object type.
    std::string name;
/// Flags applied to this type of object.
    int flags {0};  
};
}

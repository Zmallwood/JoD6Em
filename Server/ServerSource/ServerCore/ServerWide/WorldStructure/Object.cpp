/*
 * Object.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Object.hpp"

namespace JoD {
    Object::Object(std::string_view objectName)
        : m_type(Hash(objectName)) {
        
    }
}
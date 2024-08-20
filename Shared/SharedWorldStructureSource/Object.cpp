/*
 * Object.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Object.hpp"

namespace JoD {

Object::Object(std::string_view objectName, int quantity)
    : m_type(Hash(objectName)), m_creationTime(Now()), m_quantity(quantity) {}

}
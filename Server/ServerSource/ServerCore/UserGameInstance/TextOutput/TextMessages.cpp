/*
 * TextMessages.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "TextMessages.hpp"

namespace JoD {

void TextMessages::Print(std::string_view message) {
    
// Add new message to storage.
    m_data.push_back(message.data());
}

}
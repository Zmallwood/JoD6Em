/*
 * TextMessages.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "TextMessages.hpp"

namespace JoD {

    void TextMessages::Print(std::string_view message) {
        
        m_data.push_back(message.data());
    }
}
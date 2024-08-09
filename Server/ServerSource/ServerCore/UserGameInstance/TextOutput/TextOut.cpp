/*
 * TextOut.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "TextOut.hpp"

namespace JoD {

    void TextOut::Print(std::string_view message) {
        
        m_data.push_back(message.data());
    }
}
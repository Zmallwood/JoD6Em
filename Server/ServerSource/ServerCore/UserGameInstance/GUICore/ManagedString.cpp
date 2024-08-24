/*
 * ManagedString.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ManagedString.hpp"

namespace JoD {
void ManagedString::AppendText(std::string_view appendedText) {
    m_text.append(appendedText);
}
}

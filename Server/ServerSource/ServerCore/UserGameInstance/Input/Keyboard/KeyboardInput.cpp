/*
 * KeyboardInput.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "KeyboardInput.hpp"

namespace JoD {
void KeyboardInput::AppendCharacter(char c) {
    m_textInput += c;
}

std::string KeyboardInput::GetTextInputPickResult() {
    auto result = m_textInput;
    m_textInput.clear();
    return result;
}
}

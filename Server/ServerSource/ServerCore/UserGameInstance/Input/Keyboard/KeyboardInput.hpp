/*
 * KeyboardInput.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
class KeyboardInput {
  public:
    
    void AppendCharacter(char c);
    
    std::string GetTextInputPickResult();
    
  private:
    std::string m_textInput;
};
}

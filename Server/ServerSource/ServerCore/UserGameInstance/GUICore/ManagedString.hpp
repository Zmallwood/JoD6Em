/*
 * ManagedString.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
class ManagedString {
  public:
    void AppendText(std::string_view appendedText);
    
    std::string GetText() const {
        return m_text;
    }
    
  private:
    std::string m_text;
};
}

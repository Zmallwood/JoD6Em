/*
 * Graphics.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
class Graphics {
  public:
    Graphics();
    ~Graphics();
    void ClearCanvas() const;
    void PresentCanvas() const;
    GLFWwindow *GetWindow() const {
        return m_window;
    }
    
  private:
    GLFWwindow *m_window {nullptr};
    const std::string k_title {"Journey of Dreams"};
};
}

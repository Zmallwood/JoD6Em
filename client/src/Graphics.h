// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
    class Graphics
    {
      public:
        Graphics();
        void ClearCanvas();
        void PresentCanvas();

        GLFWwindow *m_window = nullptr;

      private:
        const std::string k_title = "Journey of Dreams";
    };
}
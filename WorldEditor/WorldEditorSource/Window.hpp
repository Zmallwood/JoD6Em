/*
 * Window.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class Window : public QWidget {
      public:
        explicit Window(QWidget *parent = 0);
    };
}
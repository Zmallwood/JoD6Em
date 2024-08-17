/*
 * Window.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Window.hpp"

namespace JoD {
    
Window::Window(QWidget *parent)
    : QWidget(parent) {
    setWindowState(Qt::WindowMaximized);
}

}
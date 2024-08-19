/*
 * Canvas.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class Canvas : public QLabel {
    
  protected:
    void mousePressEvent(QMouseEvent* event);
    
};

}
/*
 * Window.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class Window : public QMainWindow {
    
  public:
    
    explicit Window(QWidget *parent = 0);
    
    void paintEvent(QPaintEvent* event) override;
    
  private:
    
    QMenu m_menuFile;
    QMenu m_menuWorld;
    QMenu m_menuTools;
    QScrollArea m_scrollArea;
    QLabel m_mainLabel;
    QGridLayout m_gridLayout;
    QPushButton m_testButton;
    QImage m_image;
};

}
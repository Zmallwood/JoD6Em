/*
 * Window.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Window.hpp"
#include "QtCore/qnamespace.h"
#include "QtWidgets/qpushbutton.h"

namespace JoD {

namespace {

const int k_tileSize {60};
const int k_worldAreaWidth {100};
const int k_worldAreaHeight {100};
}

Window::Window(QWidget *parent)
    : m_scrollArea(this) {
    
    setWindowState(Qt::WindowMaximized);
    
    m_menuFile.setTitle("&File");
    m_menuFile.addAction("&New world");
    m_menuFile.addAction("&Open world");
    m_menuFile.addAction("&Save world");
    m_menuFile.addAction("&Exit");
    
    m_menuWorld.setTitle("&World");
    m_menuWorld.addAction("&Add new world area");
    
    m_menuTools.setTitle("&Tools");
    m_menuTools.addAction("&Set tools shape");
    m_menuTools.addAction("&Set tools size");
    m_menuTools.addAction("&Select tool");
    
    menuBar()->addMenu(&m_menuFile);
    menuBar()->addMenu(&m_menuWorld);
    menuBar()->addMenu(&m_menuTools);
    
    m_scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scrollArea.setWidgetResizable(false);
    
    m_testButton.setText("TEST");
    setCentralWidget(&m_scrollArea);
    
    m_scrollArea.setWidget(&m_mainLabel);
    
    m_mainLabel.setFixedSize({k_tileSize*k_worldAreaWidth,
                              k_tileSize*k_worldAreaHeight});
}

void Window::paintEvent(QPaintEvent* event) {
    
    QMainWindow::paintEvent(event);
    
    int h = m_mainLabel.height();
    int w = m_mainLabel.width();
    QPixmap pix(w, h);
    QPainter paint(&pix);
    pix.fill( Qt::gray );
    
    for (auto y = 0; y < k_worldAreaHeight; y++) {
        
        for (auto x = 0; x < k_worldAreaWidth; x++) {
            
            paint.setPen(QColor(0, 0, 0, 255));
            paint.drawRect(QRect(x*k_tileSize,y*k_tileSize,k_tileSize,k_tileSize));
        }
    }
    
    m_mainLabel.setPixmap(pix);
    
}

}
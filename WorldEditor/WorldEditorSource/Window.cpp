/*
 * Window.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Window.hpp"
#include "QtGui/qpixmap.h"
#include "World.hpp"

namespace JoD {

namespace {

const int k_tileSize {60};
const int k_worldAreaWidth {100};
const int k_worldAreaHeight {100};
}

Window::Window(QWidget *parent) {
    
    setMinimumSize({660, 660});
    setWindowState(Qt::WindowMaximized);
    
    m_menuFile.setTitle("&File");
    m_menuFile.addAction("&New world");
    m_menuFile.addAction("&Open world");
    m_menuFile.addAction("&Save world");
    m_menuFile.addAction("&Exit", [] {});
    
    m_menuWorld.setTitle("&World");
    m_menuWorld.addAction("&Add new world area");
    
    m_menuBasic.setTitle("&Basic");
    m_menuBasic.addAction("&Set ground to whole world area", [&] {
        
        auto wArea = _<World>().GetCurrWorldArea();
        
    });
    
    m_menuTools.setTitle("&Tools");
    m_menuTools.addAction("&Set tools shape");
    m_menuTools.addAction("&Set tools size");
    m_menuTools.addAction("&Select tool");
    
    menuBar()->addMenu(&m_menuFile);
    menuBar()->addMenu(&m_menuWorld);
    menuBar()->addMenu(&m_menuBasic);
    menuBar()->addMenu(&m_menuTools);
    
    m_scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scrollArea.setWidgetResizable(false);
    
    setCentralWidget(&m_mainLabel);
    
    m_mainLabel.setLayout(&m_gridLayout);
    
    m_gridLayout.addWidget(&m_scrollArea);
    
    m_scrollArea.setWidget(&m_canvasLabel);
    
    m_canvasLabel.setFixedSize(
        {k_tileSize*k_worldAreaWidth,
         k_tileSize*k_worldAreaHeight});
    
    m_sidePanel.setFixedWidth(400);
    m_gridLayout.addWidget(&m_sidePanel);
    
    m_fileSystemModel.setRootPath(QDir::currentPath());
    m_treeView.setModel(&m_fileSystemModel);
    
    m_treeView.setRootIndex(m_fileSystemModel.index(QDir::currentPath()));
    
    m_sidePanel.setLayout(&m_sidePanelLayout);
    
    m_sidePanelLayout.addWidget(&m_treeView);
    
    m_previewImage.setFixedSize({350, 350});
    
    m_sidePanelLayout.addWidget(&m_previewImage);
    
    bool ok = connect(
        &m_treeView, &QTreeView::clicked, this,
        &Window::ClickedItemInFileBrowser);
}

void Window::paintEvent(QPaintEvent* event) {
    
    QMainWindow::paintEvent(event);
    
    int h = m_canvasLabel.height();
    int w = m_canvasLabel.width();
    QPixmap pix(w, h);
    QPainter paint(&pix);
    pix.fill( Qt::gray );
    
    for (auto y = 0; y < k_worldAreaHeight; y++) {
        
        for (auto x = 0; x < k_worldAreaWidth; x++) {
            
            paint.setPen(QColor(0, 0, 0, 255));
            paint.drawRect(
                QRect(
                    x*k_tileSize,y*k_tileSize,k_tileSize,
                    k_tileSize));
        }
    }
    
    m_canvasLabel.setPixmap(pix);
    
}

void Window::ClickedItemInFileBrowser(const QModelIndex &index) {
    
    auto path = m_fileSystemModel.filePath(index);
    
    auto str = path.toStdString();
    
    if (str.substr(str.length() - 4) == ".png") {
        
        m_previewImagePixmap = QPixmap(path);
        
        m_previewImage.setPixmap(m_previewImagePixmap);
    }
}
}

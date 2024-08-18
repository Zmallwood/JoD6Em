/*
 * Window.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Window.hpp"
#include "QtGui/qpixmap.h"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "WorldStructureConstants.hpp"

namespace JoD {

namespace {

const int k_tileSize {60};

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
    m_menuBasic.addAction(
        "&Set ground to whole world area", [&] {
            
            auto wArea = _<World>().GetCurrWorldArea();
            
            for (auto y = 0; y < wArea->GetSize().h; y++) {
                
                for (auto x = 0; x < wArea->GetSize().w; x++) {
                    
                    auto tile = wArea->GetTile(x, y);
                    tile->SetGround(m_selectedImageHash);
                }
            }
            
        });
    
    m_menuTools.setTitle("&Tools");
    m_menuTools.addAction("&Set tools shape");
    m_menuTools.addAction("&Set tools size");
    m_menuTools_selectTool.setTitle("&Select tool");
    m_menuTools_selectTool.addAction("&Set ground", [&] {m_currTool = Tools::SetGround;});
    m_menuTools_selectTool.addAction("&Add object", [&] {m_currTool = Tools::AddObject;});
    m_menuTools.addMenu(&m_menuTools_selectTool);
    
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
    
    m_scrollArea.setWidget(&m_canvas);
    
    m_canvas.setFixedSize(
        {k_tileSize*WorldStructureConstants::k_worldAreaSize.w,
         k_tileSize*WorldStructureConstants::k_worldAreaSize.h});
    
    m_sidePanel.setFixedWidth(400);
    m_gridLayout.addWidget(&m_sidePanel);
    
    m_fileSystemModel.setRootPath(QCoreApplication::applicationDirPath());
    m_treeView.setModel(&m_fileSystemModel);
    
    m_treeView.setRootIndex(
        m_fileSystemModel.index(
            QCoreApplication::applicationDirPath()));
    
    m_sidePanel.setLayout(&m_sidePanelLayout);
    
    m_sidePanelLayout.addWidget(&m_treeView);
    
    m_previewImage.setFixedSize({350, 350});
    
    m_sidePanelLayout.addWidget(&m_previewImage);
    
    bool ok = connect(
        &m_treeView, &QTreeView::clicked, this,
        &Window::ClickedItemInFileBrowser);
    
    
    using iterator = std::filesystem::recursive_directory_iterator;
    
    const std::string k_relImagesPath = "Resources/Images";
    
    const auto allImagesPath = QCoreApplication::applicationDirPath().toStdString() + "/" + k_relImagesPath + "/";
    
    for (auto &entry : iterator(allImagesPath)) {
        
        // Create path string to load the images from.
        const auto absPath = entry.path().string();
        
        auto lastSlash = absPath.find_last_of("/");
        auto fileName = absPath.substr(lastSlash + 1);
        auto period = fileName.find(".");
        auto trimmedName = fileName.substr(0, period);
        
        m_images.insert({Hash(trimmedName), QImage(absPath.c_str())});        
    }
}

void Window::paintEvent(QPaintEvent* event) {
    
    QMainWindow::paintEvent(event);
    
    int h = m_canvas.height();
    int w = m_canvas.width();
    QPixmap pix(w, h);
    QPainter paint(&pix);
    pix.fill( Qt::gray );
    
    auto wArea = _<World>().GetCurrWorldArea();
    
    for (auto y = 0; y < wArea->GetSize().h; y++) {
        
        for (auto x = 0; x < wArea->GetSize().w; x++) {
            
            auto tile = wArea->GetTile(x, y);
            
            auto ground = tile->GetGround();
            
            if (m_images.contains(ground)) {
                
                // paint.fillRect(
                //     QRect(
                //         x*k_tileSize,y*k_tileSize,k_tileSize,
                //         k_tileSize), QBrush(QColor(0, 255, 0, 255)));
                paint.drawImage(QRect(x*k_tileSize, y*k_tileSize, k_tileSize, k_tileSize), m_images.at(ground));
            }
            
            // paint.setPen(QColor(0, 0, 0, 255));
            // paint.drawRect(
            //     QRect(
            //         x*k_tileSize,y*k_tileSize,k_tileSize,
            //         k_tileSize));
        }
    }
    
    m_canvas.setPixmap(pix);
    
}

void Window::ClickedItemInFileBrowser(const QModelIndex &index) {
    
    auto path = m_fileSystemModel.filePath(index);
    
    auto str = path.toStdString();
    
    if (str.substr(str.length() - 4) == ".png") {
        
        m_previewImagePixmap = QPixmap(path);
        
        m_previewImage.setPixmap(m_previewImagePixmap);
        
        auto lastSlash = str.find_last_of("/");
        auto fileName = str.substr(lastSlash + 1);
        auto period = fileName.find(".");
        auto trimmedName = fileName.substr(0, period);
        
        m_selectedImageHash = Hash(trimmedName);
    }
}

}

/*
 * Window.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "QtGui/qpixmap.h"
#include "QtWidgets/qgridlayout.h"
#include "Tools.hpp"
#include "Canvas.hpp"

namespace JoD {

class Window : public QMainWindow {
    
  public:
    
    explicit Window(QWidget *parent = 0);
    
    void paintEvent(QPaintEvent* event) override;
    
    Tools GetCurrTool() const {
        
        return m_currTool;
    }
    
    int GetSelectedImageHash() const {
        
        return m_selectedImageHash;
    }
    
  private:
    
    void ClickedItemInFileBrowser(const QModelIndex &index);
    
    QMenu m_menuFile;
    QMenu m_menuWorld;
    QMenu m_menuBasic;
    QMenu m_menuTools;
    QMenu m_menuTools_selectTool;
    QScrollArea m_scrollArea;
    Canvas m_canvas;
    QLabel m_mainLabel;
    QHBoxLayout m_gridLayout;
    QLabel m_sidePanel;
    QFileSystemModel m_fileSystemModel;
    QTreeView m_treeView;
    QVBoxLayout m_sidePanelLayout;
    QLabel m_previewImage;
    QPixmap m_previewImagePixmap;
    std::map<int, QImage> m_images;
    int m_selectedImageHash {0};
    Tools m_currTool {Tools::None};
};

}
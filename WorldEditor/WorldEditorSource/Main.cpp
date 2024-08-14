/*
 * Main.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

 #include "Window.hpp"

int main(int argc, char **argv){
    
    QApplication app (argc, argv);
    JoD::Window window;
    window.show();
    
    return app.exec();
}
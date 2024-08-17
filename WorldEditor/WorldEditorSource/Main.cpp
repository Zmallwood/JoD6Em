/*
 * Main.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

 #include "Window.hpp"

int main(int argc, char **argv) {
    
    QApplication app (argc, argv);
    
    using namespace JoD;
    
    _<Window>().show();
    
    return app.exec();
}
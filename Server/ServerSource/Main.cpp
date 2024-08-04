/*
 * Main.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ServerCore/RunGameServer.h"

int main(int argc, char *argv[]) {
    try{ // Catch all exceptions that can happen during execution.
        if (argc != 3){
            std::cerr << "Usage: JoDServer <address> <port>\n"
                      << "Example:\n"
                      << "    JoDServer 0.0.0.0 8080\n";
            return 1;
        }
        JoD::RunGameServer(argv);
    }
    catch (const std::exception &e){
        std::cout << "Error: " << e.what() << std::endl;
        return 1; // An exception occured, exit game.
    }
    return 0;
}
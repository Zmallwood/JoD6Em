/*
 * Main.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ServerCore/RunGameServer.hpp"

int main(int argc, char *argv[]) {
    
    // Catch all exceptions that can happen during execution.
    try{
        
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
        
        // An exception occured, exit game.
        return 1;
    }
    return 0;
}
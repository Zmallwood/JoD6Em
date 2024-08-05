/*
 * Main.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ClientCore/RunNewClientInstance.hpp"

int main(int argc, char *argv[]) { 
    
    // Catch all exceptions that can happen during execution.
    try{
        
        // Run new instance of the game.
        JoD::RunNewClientInstance();
    }
    catch (const std::exception &e){
        std::cout << "Error: " << e.what() << std::endl;
        
        // An exception occured, exit game.
        return 1;
    } 
    
    // No exceptions occured.
    return 0;
}  
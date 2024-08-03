/*
 * Main.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ClientCore/RunNewClientInstance.h"

int main(int argc, char *argv[]) { 
    try{ // Catch all exceptions that can happen during execution.
        jod::run_new_client_instance(); // Run new instance of the game.
    }
    catch (const std::exception &e){
        std::cout << "Error: " << e.what() << std::endl;
        return 1; // An exception occured, exit game.
    } 
    return 0; // No exceptions occured.
}  
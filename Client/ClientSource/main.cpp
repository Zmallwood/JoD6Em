/*
 * main.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ClientCore/run_new_client_instance.h"

int main(int argc, char *argv[]) {
    try{ // Catch all exceptions that can happen during execution.
        jod::run_new_client_instance(); // Run new instance of the game.
    }
    catch (const std::exception &e){
        std::cout << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE; // An exception occured, exit game.
    }
    return EXIT_SUCCESS; // No exceptions occured.
} 
/*
 * main.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "server_core/net/web_socket_server.h"
#include "theme0/scenes/world_generation/process/generate_new_world.h"

int
main(int argc, char *argv[]){
    if (argc != 3){
        std::cerr << "Usage: websocket-server-sync <address> <port>\n"
                  << "Example:\n"
                  << "    websocket-server-sync 0.0.0.0 8080\n";
        return EXIT_FAILURE;
    }
    using namespace jod;
    try{
        srand(time(0));
        generate_new_world();
        _<web_socket_server>().start(argv[1], argv[2]);
    }
    catch (const std::exception &e){
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
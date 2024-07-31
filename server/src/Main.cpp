// Copyright (c) 2024 Andreas Åkerberg.
#include "Net.h"
#include "WorldGeneration.h"

int main(int argc, char *argv[]){
    if (argc != 3){
        std::cerr << "Usage: websocket-server-sync <address> <port>\n"
                  << "Example:\n"
                  << "    websocket-server-sync 0.0.0.0 8080\n";
        return EXIT_FAILURE;
    }
    using namespace jod;
    try{
        srand(time(0));
        GenerateNewWorld();
        _<WebSocketServer>().Start(argv[1], argv[2]);
    }
    catch (const std::exception &e){
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
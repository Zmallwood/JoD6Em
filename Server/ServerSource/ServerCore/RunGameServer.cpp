/*
 * RunGameServer.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RunGameServer.h"
#include "ServerCore/ServerWide/WorldGeneration/GenerateNewWorld.h"
#include "Net/RunWebSocketServer.h"

namespace JoD {
    void RunGameServer(char **argv) {
        srand(time(0));
        generate_new_world();
        RunWebSocketServer(argv[1], argv[2]);
    }
}
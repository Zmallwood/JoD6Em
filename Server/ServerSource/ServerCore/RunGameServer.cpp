/*
 * RunGameServer.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RunGameServer.h"
#include "Theme0/Scenes/WorldGeneration/Process/GenerateNewWorld.h"
#include "Net/RunWebSocketServer.h"

namespace jod {
    void RunGameServer(char **argv) {
        srand(time(0));
        generate_new_world();
        RunWebSocketServer(argv[1], argv[2]);
    }
}
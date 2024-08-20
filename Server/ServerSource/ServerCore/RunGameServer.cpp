/*
 * RunGameServer.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RunGameServer.hpp"
#include "ServerCore/ServerWide/WorldGeneration/GenerateNewWorld.hpp"
#include "Net/RunWSServer.hpp"
#include "WorldProcessing/BeginProcessWorld.hpp"

namespace JoD {
void RunGameServer(char **argv) {
    // Make random number generation unique each application start.
    srand(time(0));
    // Generate new game world at application start.
    GenerateNewWorld();
    // Start the world process loop in its own thread.
    BeginProcessWorld();
    // Start the websocket server, accepting incoming connections
    // and handling them through connection life times.
    RunWSServer(argv[1], argv[2]);
}
}
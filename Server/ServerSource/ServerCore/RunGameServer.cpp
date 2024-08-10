/*
 * RunGameServer.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RunGameServer.hpp"
#include "ServerCore/ServerWide/WorldGeneration/GenerateNewWorld.hpp"
#include "Net/RunWebSocketServer.hpp"
#include "WorldProcessing/BeginProcessWorld.hpp"

namespace JoD {
    
    void RunGameServer(char **argv) {
        
        srand(time(0));
        
        GenerateNewWorld();
        
        BeginProcessWorld();
        
        RunWebSocketServer(argv[1], argv[2]);
    }
}
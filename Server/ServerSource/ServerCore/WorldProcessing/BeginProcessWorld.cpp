/*
 * BeginProcessWorld.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "BeginProcessWorld.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"

namespace JoD {
    
    namespace {
        
        void RunWorldProcessingLoop();
    }

    void BeginProcessWorld() {
        
        std::thread(&RunWorldProcessingLoop).detach();
    }
    
    namespace {
        
        void RunWorldProcessingLoop() {
            
            while (true) {
                
                auto worldArea = _<World>().GetCurrentWorldArea();
                
                std::this_thread::sleep_for(std::chrono::milliseconds(70));
            }
        }
    }
}
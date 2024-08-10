/*
 * BeginProcessWorld.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "BeginProcessWorld.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/Object.hpp"

namespace JoD {
    
    namespace {
        
        void RunWorldProcessingLoop();
        
        static constexpr Duration k_remainsStayDuration {Millis(5000)};
    }

    void BeginProcessWorld() {
        
        std::thread(&RunWorldProcessingLoop).detach();
    }
    
    namespace {
        
        void RunWorldProcessingLoop() {
            
            while (true) {
                
                auto worldArea = _<World>().GetCurrentWorldArea();
                
                for (auto y = 0; y < worldArea->GetSize().h; y++) {
                    
                    for (auto x = 0; x < worldArea->GetSize().w; x++) {
                        
                        auto tile = worldArea->GetTile(x, y);
                        
                        auto object = tile->GetObject();
                        
                        if (object) {
                            
                            if (object->GetType() == Hash("ObjectBoneRemains")) {
                                
                                if (Now() > object->GetCreationTime() + k_remainsStayDuration) {
                                    
                                    tile->SetObject(nullptr);
                                }
                            }
                        }
                    }
                }
                
                std::this_thread::sleep_for(std::chrono::milliseconds(70));
            }
        }
    }
}
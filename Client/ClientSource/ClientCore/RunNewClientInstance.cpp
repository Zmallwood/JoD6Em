/*
 * RunNewClientInstance.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RunNewClientInstance.hpp"
#include "ClientEngine.hpp"

namespace JoD {
    
    void RunNewClientInstance() {
        
        // Access ClientEngine and run it.
        _<ClientEngine>().Run();  
    }
}
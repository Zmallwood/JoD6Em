/*
 * RunNewClientInstance.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RunNewClientInstance.h"
#include "ClientEngine.h"

namespace JoD {
    void RunNewClientInstance()      {
        _<ClientEngine>().Run(); // Access ClientEngine and run it.
    }
}
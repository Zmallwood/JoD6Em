/*
 * RunNewClientInstance.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RunNewClientInstance.h"
#include "ClientEngine.h"

namespace jod {
    void run_new_client_instance()      {
        _<client_engine>().run(); // Access ClientEngine and run it.
    }
}
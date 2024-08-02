// run_new_client_instance.cpp
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
//

#include "run_new_client_instance.h"
#include "client_engine.h"

namespace jod {
    void
    run_new_client_instance(){
        _<client_engine>().run(); // Access ClientEngine and run it.
    }
}
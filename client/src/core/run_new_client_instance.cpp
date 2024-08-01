// Copyright (c) 2024 Andreas Åkerberg.

#include "run_new_client_instance.h"
#include "core.h"

namespace jod {
    void
    run_new_client_instance(){
        _<client_engine>().run(); // Access ClientEngine and run it.
    }
}
/*
 * DB.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "DB.hpp"

namespace JoD {
DB::DB() {
    SetupDB();
}

void DB::RegisterNewUser(std::string_view userName, int passwordHash) {}


void DB::SetupDB() {}
}

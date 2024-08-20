/*
 * ObjectEntry.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
struct ObjectEntry {
    std::string name;
    int flags {0};  
};
}
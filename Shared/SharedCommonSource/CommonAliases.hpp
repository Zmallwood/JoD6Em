/*
 * Aliases.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include <chrono>

namespace JoD {

using TimePoint =  ///< Point in time.
                  std::chrono::high_resolution_clock::time_point;

using Duration =   ///< Duration in time.
                 std::chrono::high_resolution_clock::duration;

using Millis =     ///< Milliseconds.
               std::chrono::milliseconds;

static auto Now =  ///< Get current point in time.
                  std::chrono::high_resolution_clock::now;
                  
}
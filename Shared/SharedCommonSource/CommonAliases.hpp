/*
 * Aliases.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include <chrono>

namespace JoD {
/// Point in time.
using TimePoint = std::chrono::high_resolution_clock::time_point;
/// Duration in time.
using Duration = std::chrono::high_resolution_clock::duration;
/// Milliseconds.
using Millis = std::chrono::milliseconds;
/// Get current point in time.
static auto Now = std::chrono::high_resolution_clock::now;
}

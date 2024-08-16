/*
 * MenuEntry.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

    struct MenuEntry {

        std::string label;

        std::function<void()> action;

        BoxF bounds;
    };
}

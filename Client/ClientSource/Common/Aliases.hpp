/*
 * Aliases.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    using RID = GLuint; ///< Resource ID.
    
    static auto GetTicks = SDL_GetTicks; ///< Current number of ticks now.
}
// aliases.h
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
//

namespace jod {
    using rid = GLuint; //!< Resource ID.
    
    static auto get_ticks = SDL_GetTicks; //!< Current number of ticks now.
}
// Copyright (c) 2024 Andreas Åkerberg.

#include "sdl_deleter.h"

namespace jod {
    void
    sdl_deleter::operator()(SDL_Window *window) const {
        SDL_DestroyWindow(window); // Destroy SDL window object.
    }
    
    void
    sdl_deleter::operator()(SDL_Renderer *renderer) const {
        SDL_DestroyRenderer(renderer); // Destroy SDL renderer object.
    }
    
    void
    sdl_deleter::operator()(SDL_Surface *surface) const {
        SDL_FreeSurface(surface); // Free SDL surface object.
    }
    
    void
    sdl_deleter::operator()(SDL_Texture *texture) const {
        SDL_DestroyTexture(texture); // Destroy SDL texture object.
    }
    
    void
    sdl_deleter::operator()(TTF_Font *font) const {
        TTF_CloseFont(font); // Close SDL_ttf font object.
    }
}
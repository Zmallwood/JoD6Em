/*
 * SDLDeleter.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "SDLDeleter.hpp"

namespace JoD {
    void SDLDeleter::operator()(SDL_Window *window) const {
        SDL_DestroyWindow(window); // Destroy SDL window object.
    }
    
    void SDLDeleter::operator()(SDL_Renderer *renderer) const {
        SDL_DestroyRenderer(renderer); // Destroy SDL renderer object.
    }
    
    void SDLDeleter::operator()(SDL_Surface *surface) const {
        SDL_FreeSurface(surface); // Free SDL surface object.
    }
    
    void SDLDeleter::operator()(SDL_Texture *texture) const {
        SDL_DestroyTexture(texture); // Destroy SDL texture object.
    }
    
    void SDLDeleter::operator()(TTF_Font *font) const {
        TTF_CloseFont(font); // Close SDL_ttf font object.
    }
}
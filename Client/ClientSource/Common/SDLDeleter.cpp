/*
 * SDLDeleter.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "SDLDeleter.hpp"

namespace JoD {

void SDLDeleter::operator()(SDL_Window *window) const {
    
// Destroy SDL window object.
    SDL_DestroyWindow(window);
}

void SDLDeleter::operator()(SDL_Renderer *renderer) const {
    
// Destroy SDL renderer object.
    SDL_DestroyRenderer(renderer);
}

void SDLDeleter::operator()(SDL_Surface *surface) const {
    
// Free SDL surface object.
    SDL_FreeSurface(surface);
}

void SDLDeleter::operator()(SDL_Texture *texture) const {
    
// Destroy SDL texture object.
    SDL_DestroyTexture(texture);
}

void SDLDeleter::operator()(TTF_Font *font) const {
    
// Close SDL_ttf font object.
    TTF_CloseFont(font);
}

}
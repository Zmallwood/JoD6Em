/*
 * SDLDeleter.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    /// @brief Helper class to automatically free allocated resources for SDL objects.
    class SDLDeleter {
    public:
        /// @brief Cleanup of SDL_Window object.
        /// @param window Object to cleanup.
        void operator()(SDL_Window *window) const;
        
        /// @brief Cleanup of SDL_Renderer object.
        /// @param renderer Object to cleanup.
        void operator()(SDL_Renderer *renderer) const;
        
        /// @brief Cleanup of SDL_Surface object.
        /// @param surface Object to cleanup.
        void operator()(SDL_Surface *surface) const;
        
        /// @brief Cleanup of SDL_Texture object.
        /// @param texture Object to cleanup.
        void operator()(SDL_Texture *texture) const;
        
        /// @brief Cleanup of TTF_Font object.
        /// @param font Object to cleanup.
        void operator()(TTF_Font *font) const;
    };
}
// Copyright (c) 2024 Andreas Åkerberg.

#include "util.h"
#include "graphics.h"

namespace jod {
    void
    sdl_deleter::operator()(SDL_Window *window) const {
        SDL_DestroyWindow(window);
    }
    
    void
    sdl_deleter::operator()(SDL_Renderer *renderer) const {
        SDL_DestroyRenderer(renderer);
    }
    
    void
    sdl_deleter::operator()(SDL_Surface *surface) const {
        SDL_FreeSurface(surface);
    }
    
    void
    sdl_deleter::operator()(SDL_Texture *texture) const {
        SDL_DestroyTexture(texture);
    }
    
    void
    sdl_deleter::operator()(TTF_Font *font) const {
        TTF_CloseFont(font);
    }
    
    size
    get_canvas_size(){
        int w, h; // To store dimensions in pixels.
        // Use GLFW to get canvas size.
        glfwGetWindowSize(_<graphics>().m_window, &w, &h);
        return {w, h};
    }
    
    pointf
    get_mouse_position(){
        double xpos, ypos; // Declare variables to store mouse coordinates in pixels.
        // Use GLFW to get current mouse coordinates.
        glfwGetCursorPos(_<graphics>().m_window, &xpos, &ypos);
        auto canvasSize = get_canvas_size(); // Get canvas size.
        // And use it to convert pixel coordinates to fractal coordinates.
        auto mousePosition = pointf{
            static_cast<float>(xpos) / canvasSize.w,
            static_cast<float>(ypos) / canvasSize.h};
        return mousePosition;
    }
    
    float
    get_aspect_ratio(){
        auto canvasSize = get_canvas_size(); // Get canvas dimensions.
        // And calculate the ratio between them.
        auto aspectRatio = static_cast<float>(canvasSize.w) / canvasSize.h;
        return aspectRatio;
    }
    
    float
    convert_width_to_height(float width){
        // Use aspect ratio to convert from width to corresponding height.
        return width * get_aspect_ratio();
    }
    
    float
    convert_height_to_width(float height){
        // Use aspect ratio to convert from height to corresponding width.
        return height / get_aspect_ratio();
    }
    
    std::string
    file_extension(std::string_view absPath){
        // Find last occurrence of '.' and keep the part following it.
        auto extension = absPath.substr(absPath.find_last_of('.') + 1);
        return extension.data();
    }
    
    std::string
    filename_no_extension(std::string_view absPath){
        // Find last occurence of '/' and get the part following it.
        auto nameWithExt =
            std::string(absPath.substr(absPath.find_last_of('/') + 1));
        // Then only keep the part preceeding the last occurrence of '.'.
        auto fileName = nameWithExt.substr(0, nameWithExt.find_last_of('.'));
        return fileName;
    }
}
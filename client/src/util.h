// Copyright (c) 2024 Andreas Åkerberg.
#pragma once
namespace jod {
    using RID = GLuint;
    static auto get_ticks = SDL_GetTicks;
    
    class sdl_deleter {
    public:
        void operator()(SDL_Window *window) const;
        void operator()(SDL_Renderer *renderer) const;
        void operator()(SDL_Surface *surface) const;
        void operator()(SDL_Texture *texture) const;
        void operator()(TTF_Font *font) const;
    };
    
    Size get_canvas_size();
    PointF get_mouse_position();
    float get_aspect_ratio();
    float convert_width_to_height(float width);
    float convert_height_to_width(float height);
    std::string file_extension(std::string_view absPath);
    std::string filename_no_extension(std::string_view absPath);
}
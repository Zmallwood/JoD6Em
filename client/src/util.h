// Copyright (c) 2024 Andreas Åkerberg.
#pragma once
namespace jod {
    using RID = GLuint;
    static auto Ticks = SDL_GetTicks;
    
    class SDLDeleter {
    public:
        void operator()(SDL_Window *window) const;
        void operator()(SDL_Renderer *renderer) const;
        void operator()(SDL_Surface *surface) const;
        void operator()(SDL_Texture *texture) const;
        void operator()(TTF_Font *font) const;
    };
    
    Size GetCanvasSize();
    PointF GetMousePosition();
    float GetAspectRatio();
    float ConvertWidthToHeight(float width);
    float ConvertHeightToWidth(float height);
    std::string FileExtension(std::string_view absPath);
    std::string FilenameNoExtension(std::string_view absPath);
}
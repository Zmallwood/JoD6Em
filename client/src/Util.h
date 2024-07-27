#pragma once

namespace jod
{
    using RID = GLuint;

    static auto Ticks = SDL_GetTicks;

    template <class T>
    T &_()
    {
        static T instance;
        return instance;
    }

    class SDLDeleter
    {
      public:
        void operator()(SDL_Window *window) const;
        void operator()(SDL_Renderer *renderer) const;
        void operator()(SDL_Surface *surface) const;
        void operator()(SDL_Texture *texture) const;
        void operator()(TTF_Font *font) const;
    };

    int Hash(std::string_view text);
    std::string FileExtension(std::string_view absPath);
    std::string FilenameNoExtension(std::string_view absPath);
}
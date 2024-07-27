#include "Util.h"

namespace jod
{
    void SDLDeleter::operator()(SDL_Window *window) const
    {
        SDL_DestroyWindow(window);
    }

    void SDLDeleter::operator()(SDL_Renderer *renderer) const
    {
        SDL_DestroyRenderer(renderer);
    }

    void SDLDeleter::operator()(SDL_Surface *surface) const
    {
        SDL_FreeSurface(surface);
    }

    void SDLDeleter::operator()(SDL_Texture *texture) const
    {
        SDL_DestroyTexture(texture);
    }

    void SDLDeleter::operator()(TTF_Font *font) const
    {
        TTF_CloseFont(font);
    }

    int Hash(std::string_view text)
    {
        unsigned long hash = 5381;
        for (size_t i = 0; i < text.size(); ++i)
            hash = 33 * hash + (unsigned char)text[i];
        return static_cast<int>(hash);
    }

    std::string FileExtension(std::string_view absPath)
    {
        /* Find last occurrence of '.' and keep the part following it. */
        auto extension = absPath.substr(absPath.find_last_of('.') + 1);
        return extension.data();
    }

    std::string FilenameNoExtension(std::string_view absPath)
    {
        /* 1) Find last occurence of '/' and get the part following it.
         * 2) Then only keep the part preceeding the last occurrence of '.'. */
        auto nameWithExt = std::string(absPath.substr(absPath.find_last_of('/') + 1));
        auto fileName = nameWithExt.substr(0, nameWithExt.find_last_of('.'));
        return fileName;
    }
}
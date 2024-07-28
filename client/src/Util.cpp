// Copyright (c) 2024 Andreas Åkerberg.

#include "Util.h"

#include "Graphics.h"

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

  Size GetCanvasSize()
  {
    /* To store dimensions in pixels. */

    int w;
    int h;

    /* Use GLFW to get canvas size. */

    glfwGetWindowSize(_<Graphics>().m_window, &w, &h);

    return {w, h};
  }

  PointF GetMousePosition()
  {
    /* Declare variables to store mouse coordinates in pixels. */

    double xpos, ypos;

    /* Use GLFW to get current mouse coordinates. */

    glfwGetCursorPos(_<Graphics>().m_window, &xpos, &ypos);

    /* Get canvas size. */

    auto canvasSize = GetCanvasSize();

    /* And use it to convert pixel coordinates to fractal coordinates. */

    auto mousePosition =
        PointF{static_cast<float>(xpos) / canvasSize.w, static_cast<float>(ypos) / canvasSize.h};

    return mousePosition;
  }

  float GetAspectRatio()
  {
    /* Get canvas dimensions. */

    auto canvasSize = GetCanvasSize();

    /* And calculate the ratio between them. */

    auto aspectRatio = static_cast<float>(canvasSize.w) / canvasSize.h;

    return aspectRatio;
  }

  float ConvertWidthToHeight(float width)
  {
    /* Use aspect ratio to convert from width to corresponding height. */

    return width * GetAspectRatio();
  }

  float ConvertHeightToWidth(float height)
  {
    /* Use aspect ratio to convert from height to corresponding width. */

    return height / GetAspectRatio();
  }

  std::string FileExtension(std::string_view absPath)
  {
    /* Find last occurrence of '.' and keep the part following it. */

    auto extension = absPath.substr(absPath.find_last_of('.') + 1);

    return extension.data();
  }

  std::string FilenameNoExtension(std::string_view absPath)
  {
    /* Find last occurence of '/' and get the part following it. */

    auto nameWithExt = std::string(absPath.substr(absPath.find_last_of('/') + 1));

    /* Then only keep the part preceeding the last occurrence of '.'. */
    
    auto fileName = nameWithExt.substr(0, nameWithExt.find_last_of('.'));

    return fileName;
  }
}
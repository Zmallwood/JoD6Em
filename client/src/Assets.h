// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
    class ImageBank
    {
      public:
        ImageBank();
        ~ImageBank();
        GLuint GetImage(std::string_view imageName);
        GLuint GetImage(int imageNameHash);
        GLuint CreateBlankImage(std::string_view uniqueImageName);

      private:
        void LoadImages();
        GLuint LoadSingleImage(std::string_view absFilePath);
        SDL_Surface *LoadImageData(const char *filename);

        std::map<int, GLuint> m_images;
        const std::string k_relImagesPath{"Resources/Images"};
    };
}
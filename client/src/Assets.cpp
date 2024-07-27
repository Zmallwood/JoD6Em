// Copyright (c) 2024 Andreas Åkerberg.

#include "Assets.h"

namespace jod
{
    ImageBank::ImageBank()
    {
        /* Load all images in images path. */
        LoadImages();
    }

    ImageBank::~ImageBank()
    {
        /* Iterate through all the loaded images. */
        for (const auto &img : m_images)
            /* Free every allocated image resource */
            glDeleteTextures(1, &img.second);
    }

    GLuint ImageBank::GetImage(std::string_view imageName)
    {
        /* Hash the image name and call the other GetImage method. */
        return GetImage(Hash(imageName));
    }

    GLuint ImageBank::GetImage(int imageNameHash)
    {
        /* Iterate through all the loaded images. */
        for (auto img : m_images)
            /* If its key, being the hash of the image name, equals
               the hash of the specified name, then, return this image ID */
            if (img.first == imageNameHash)
                return img.second;
        /* No image with the name found, return fail value. */
        return -1;
    }

    GLuint ImageBank::CreateBlankImage(std::string_view uniqueImageName)
    {
        /* Generate new image resource and get its ID. */
        GLuint texID;
        glGenTextures(1, &texID);
        /* Insert new image entry with image name hash as key
           and the new ID as value. */
        m_images.insert({Hash(uniqueImageName), texID});
        /* Return the ID of the newly created blank image resource.*/
        return texID;
    }

    void ImageBank::LoadImages()
    {
        using iterator = std::filesystem::recursive_directory_iterator;
        auto allImagesPath = k_relImagesPath + "/";
        for (auto &entry : iterator(allImagesPath))
        {
            /* Create path string to load the images from. */
            auto absPath = entry.path().string();
            /* Only handle files with png extenstion. */
            if (FileExtension(absPath) != "png")
                continue;
            /* Load the current file as an image resource. */
            auto texID = LoadSingleImage(absPath);
            /* Extract its pure name without path or extension. */
            auto imageName = FilenameNoExtension(absPath);
            /* Insert a new entry into the images storage, with the
               image name hash as key and the resource ID as value.*/
            m_images.insert({Hash(imageName), texID});
        }
    }

    GLuint ImageBank::LoadSingleImage(std::string_view absFilePath)
    {
        /* Declare variable to hold the resulting ID for the loaded image file. */
        GLuint texID;
        /* Get image data from the image file. */
        auto surf = LoadImageData(absFilePath.data());
        /* We will work with 2D textures. */
        glEnable(GL_TEXTURE_2D);
        /* Generate a new OpenGL texture and get its ID. */
        glGenTextures(1, &texID);
        /* Use the newly created OpenGL texture. */
        glBindTexture(GL_TEXTURE_2D, texID);
        /* Apply necessary texture parameters. */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        /* Transfer image data from SDL surface to OpenGL texture resource depending on
           if the image format is RGB or RGBA (with or without alpha channel). */
        if (surf->format->BytesPerPixel == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels);
        /* Free SDL surface resource, its not needed anymore as the image data is
            stored in the OpenGL texture now. */
        SDL_FreeSurface(surf);
        /* Return the previously generated resource ID. */
        return texID;
    }

    SDL_Surface *ImageBank::LoadImageData(const char *filename)
    {
        int width;
        int height;
        int bytesPerPixel;
        /* Read data. */
        void *data = stbi_load(filename, &width, &height, &bytesPerPixel, 0);
        /* Calculate pitch. */
        int pitch;
        pitch = width * bytesPerPixel;
        pitch = (pitch + 3) & ~3;
        /* Setup relevance bitmask. */
        int rMask;
        int gMask;
        int bMask;
        int aMask;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
        rMask = 0x000000FF;
        gMask = 0x0000FF00;
        bMask = 0x00FF0000;
        aMask = (bytesPerPixel == 4) ? 0xFF000000 : 0;
#else
        int s = (bytesPerPixel == 4) ? 0 : 8;
        rMask = 0xFF000000 >> s;
        gMask = 0x00FF0000 >> s;
        bMask = 0x0000FF00 >> s;
        aMask = 0x000000FF >> s;
#endif
        /* Create SDL surface from image data. */
        auto surface =
            SDL_CreateRGBSurfaceFrom(data, width, height, bytesPerPixel * 8, pitch, rMask, gMask, bMask, aMask);
        /* If surface creation failed, then free image data and return nullptr. */
        if (!surface)
        {
            stbi_image_free(data);
            return nullptr;
        }
        /* Else if surface creation was successful, return the surface. */
        return surface;
    }
}
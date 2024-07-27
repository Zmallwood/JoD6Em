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
        /* 1) Iterate through all the loaded images.
         * 2) Free every allocated image resource */
        for (const auto &img : m_images)
            glDeleteTextures(1, &img.second);
    }

    GLuint ImageBank::GetImage(std::string_view imageName)
    {
        /* Hash the image name and call the other GetImage method. */
        return GetImage(Hash(imageName));
    }

    GLuint ImageBank::GetImage(int imageNameHash)
    {
        /* 1) Iterate through all the loaded images.
         * 2) If its key, being the hash of the image name, equals
         *    the hash of the specified name,
         *    then, return this image ID
         * 3) No image with the name found, return fail value. */
        for (auto img : m_images)
            if (img.first == imageNameHash)
                return img.second;
        return -1;
    }

    GLuint ImageBank::CreateBlankImage(std::string_view uniqueImageName)
    {
        /* 1) Generate new image resource and get its ID.
         * 2) Insert new image entry with image name hash as key
         *    and the new ID as value.
         * 3) return the ID of the newly created blank image resource.*/
        GLuint texID;
        glGenTextures(1, &texID);
        m_images.insert({Hash(uniqueImageName), texID});
        return texID;
    }

    void ImageBank::LoadImages()
    {
        /* 1) Create path string to load the images from.
         * 2) Only handle files with png extenstion.
         * 3) Load the current file as an image resource.
         * 4) Extract its pure name without path or extension.
         * 5) Insert a new entry into the images storage, with the
         *    image name hash as key and the resource ID as value.*/
        using iterator = std::filesystem::recursive_directory_iterator;
        auto allImagesPath = k_relImagesPath + "/";
        for (auto &entry : iterator(allImagesPath))
        {
            auto absPath = entry.path().string();
            if (FileExtension(absPath) != "png")
                continue;
            auto texID = LoadSingleImage(absPath);
            auto imageName = FilenameNoExtension(absPath);
            m_images.insert({Hash(imageName), texID});
        }
    }

    GLuint ImageBank::LoadSingleImage(std::string_view absFilePath)
    {
        /* 1) Declare variable to hold the resulting ID for the loaded image file.
         * 2) Get image data from the image file.
         * 3) We will work with 2D textures.
         * 4) Generate a new OpenGL texture and get its ID.
         * 5) Use the newly created OpenGL texture.
         * 6) Apply necessary texture parameters. */
        GLuint texID;
        auto surf = LoadImageData(absFilePath.data());
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        /* 1) if image format is RGBA (with alpha channel),
         *    then transfer image data from SDL surface to OpenGL texture resource.
         *    Else if image format is RGB (without alpha channel),
         *    then transfer image data from SDL surface to OpenGL texture resource.
         * 2) Free SDL surface resource, its not needed anymore as the image data is
         *    stored in the OpenGL texture now.
         * 3) Return the previously generated resource ID. */
        if (surf->format->BytesPerPixel == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels);
        SDL_FreeSurface(surf);
        return texID;
    }

    SDL_Surface *ImageBank::LoadImageData(const char *filename)
    {
        /* 1) Read data.
         * 2) Calculate pitch.
         * 3) Setup relevance bitmask.
         * 4) Create SDL surface from image data.
         * 5) If surface creation failed, then free image data and return nullptr.
         * 6) Else if surface creation was successful, return the surface. */
        int width;
        int height;
        int bytesPerPixel;
        void *data = stbi_load(filename, &width, &height, &bytesPerPixel, 0);
        int pitch;
        pitch = width * bytesPerPixel;
        pitch = (pitch + 3) & ~3;
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
        auto surface =
            SDL_CreateRGBSurfaceFrom(data, width, height, bytesPerPixel * 8, pitch, rMask, gMask, bMask, aMask);
        if (!surface)
        {
            stbi_image_free(data);
            return nullptr;
        }
        return surface;
    }
}
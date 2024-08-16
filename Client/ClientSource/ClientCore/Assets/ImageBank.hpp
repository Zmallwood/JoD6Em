/*
 * ImageBank.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ImageEntry.hpp"

namespace JoD {

    ///
    /// Loads and provides image resources.
    ///
    /// @details Used as a singleton during the whole application session.
    ///          When singleton instance is created the construvtor calls
    ///          the LoadImages() function which in turn loads all PNG-files
    ///          in the images path, defined by k_relImagesPath.
    ///
    class ImageBank {

      public:
        ///
        /// Construct a new Image Bank object.
        ///
        /// @details Calls the LoadImages() function and nothing else.
        ///
        ImageBank();

        ///
        /// Destroy the image bank object.
        ///
        /// @details Deletes all GL textures in m_images.
        ///
        ~ImageBank();

        ///
        /// Get the Image object.
        ///
        /// @param imageName of image, corresponding to filename wihtout extension.
        /// @return GLuint Resource ID of obtained image object.
        ///
        /// @details Obtains the hash code for the imageName parameter and checks if it
        ///          exists as a key in m_images.
        ///
        std::optional<GLuint> GetImage(std::string_view imageName) const;

        ///
        /// Get the Image object.
        ///
        /// @param imageNameHash Hash code of image name, corresponding to hash code of filename
        ///                      wihtout extension.
        /// @return GLuint Resource ID of obtained image object.
        ///
        /// @details Checks if the imageNameHash parameter exists as a key
        ///          in m_images.
        ///
        std::optional<GLuint> GetImage(int imageNameHash) const;

        ///
        /// Create a blank image object.
        ///
        /// @param uniqueImageName Name of newly created blank image.
        /// @return GLuint Resource ID of created image.
        ///
        /// @details Generates a new OpenGL texture and does nothing
        ///          with the texture. Inserts the ID of the texture
        ///          into m_images with the hash code of the uniqueImageName
        ///          parameter as key.
        ///
        GLuint CreateBlankImage(std::string_view uniqueImageName);

        ///
        ///  Get image dimensions for provided image name hash code.
        ///
        /// @param imageNameHash Image name hash code to get dimensions for.
        /// @return Size Image dimensions.
        ///
        /// @details Checks if an entry exists in m_images with the
        ///          imageNameHash parameter as key. If so, gets the
        ///          entrys dimension-variable and returns it. If no
        ///          entry exists with the value of the imageNameHash
        ///          parameter, then it returns an empty size: {0, 0}-
        ///
        Size GetImageDimensions(int imageNameHash) const;

      private:
        ///
        /// Loads all images from file system and storesboth the images and their dimensions.
        ///
        /// @details Constructs the absolute path to the image resources folder, determined
        ///          by k_relImagesPath. Then iterates over all the files in this folder.
        ///          For every file a check is made if it has a .png extension. If so, then
        ///          first the image is loaded and obtained as a ImageEntry object. Then the
        ///          files pure name without path or extension is extracted. Lastly the image
        ///          entry is inserted into m_images with the key being the hash code of the
        ///          pure name, without path or extension, of the image file.
        ///
        void LoadImages();

        std::map<int, ImageEntry> m_images;                    ///< Stores images as entries by image name hash code.
        const std::string k_relImagesPath{"Resources/Images"}; ///< Path to images location.
    };
}

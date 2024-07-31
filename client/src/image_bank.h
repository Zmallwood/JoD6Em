// Copyright (c) 2024 Andreas Åkerberg.
#pragma once
namespace jod {
    /////////////////////////////////////////////////
    /// \brief Loads and provides image resources.
    /////////////////////////////////////////////////
    class image_bank {
    public:
        /////////////////////////////////////////////////
        /// \brief Construct a new Image Bank object.
        /////////////////////////////////////////////////
        image_bank();
        /////////////////////////////////////////////////
        /// \brief Destroy the Image Bank object.
        /////////////////////////////////////////////////
        ~image_bank();
        /////////////////////////////////////////////////
        /// \brief Get the Image object.
        /// \param imageName Name of image, corresponding to filename wihtout extension.
        /// \return GLuint Resource ID of obtained image object.
        /////////////////////////////////////////////////
        GLuint get_image(
            std::string_view imageName) const;
        /////////////////////////////////////////////////
        /// \brief Get the Image object.
        /// \param imageNameHash Hash code of image name, corresponding to hash code of filename
        ///                      wihtout extension.
        /// \return GLuint Resource ID of obtained image object.
        /////////////////////////////////////////////////
        GLuint get_image(
            int imageNameHash) const;
        /////////////////////////////////////////////////
        /// \brief Create a Blank Image object.
        /// \param uniqueImageName Name of newly created blank image.
        /// \return GLuint GLuint Resource ID of created image.
        /////////////////////////////////////////////////
        GLuint create_blank_image(
            std::string_view uniqueImageName);
    private:
        void load_images();
        
        std::map<int, GLuint> m_images; ///< Stores images by image name hash code.
        const std::string k_relImagesPath{"Resources/Images"}; ///< Path to images location.
    };
}
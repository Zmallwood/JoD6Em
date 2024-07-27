// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
    /**
     * @brief Start new game instance.
     *
     */
    void RunNewClientInstance();

    /**
     * @brief Engine for the client.
     *
     */
    class ClientEngine
    {
      public:
        /**
         * @brief Run the client engine.
         *
         */
        void Run() const;

        /**
         * @brief Poll input events from user.
         *
         */
        void PollEvents();

        /**
         * @brief Engine is running as long as this is set to true.
         *
         */
        bool m_running = true;
    };

    /**
     * @brief Holds data for doing a image drawing operation, created when such a request is
     *        incoming from the server.
     *
     */
    class ImageDrawInstruction
    {
      public:
        /**
         * @brief ID for an image resource previously allocated.
         *
         */
        RID m_rid = -1;

        /**
         * @brief Hash code of image name to draw.
         *
         */
        int m_imageNameHash = 0;

        /**
         * @brief Destination rectangle to draw the image at.
         *
         */
        RectF m_dest;
    };

    /**
     * @brief Holds latest set of rendering instructions and executes them.
     *
     */
    class Canvas
    {
      public:
        /**
         * @brief Construct a new Canvas object.
         *
         */
        Canvas();

        /**
         * @brief Add new image draw instruction to group, called on request from server.
         *
         * @param imageNameHash Hash code of image name to draw.
         * @param dest Destination rectangle to draw the image at.
         */
        void AddImageDrawInstruction(int imageNameHash, RectF dest);

        /**
         * @brief Copies the buffered render instructions to the active render instructions set.
         *
         */
        void PresentNewCanvas();

        /**
         * @brief Performs all rendering instructions by performing rendering instructions to the
         *        web browser.
         *
         */
        void DrawCanvas();

      private:
        /**
         * @brief Holds the image draw instructions that are executed each call to DrawCanvas().
         *
         */
        std::vector<ImageDrawInstruction> m_imageDrawInstructions;

        /**
         * @brief Holds the buffer for the next set of draw of instructions that will be copied to
         * the current one in PresentNewCanvas().
         *
         */
        std::vector<ImageDrawInstruction> m_imageDrawInstructionsBuffer;

        /**
         * @brief A set of preallocated resource IDs used for drawing images, created in the
         * constructor.
         *
         */
        std::vector<RID> m_rids;

        /**
         * @brief Number of preallocated resource IDs created for the image draw instructions. No
         *        more images than this value can be rendererd in a single game frame.
         *
         */
        const int k_maxNumDrawInstructions = 200;
    };
}
/*
 * RenderInstructionsManager.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ImageDrawInstruction.hpp"

namespace JoD {
    
    ///
    /// Holds latest set of rendering instructions and executes them.
    ///
    class RenderInstrutionsManager {
        
      public:
        ///
        /// Construct a new Render Instructions Manager object.
        ///
        RenderInstrutionsManager();
        
        ///
        /// Add new image draw instruction to group, called on request from server.
        ///
        /// @param imageNameHash Hash code of image name to draw.
        /// @param destination Destination rectangle to draw the image at.
        ///
        void AddImageDrawInstruction(int imageNameHash, RectF destination);
        
        void AddTextDrawInstruction(std::string_view text, PointF position);
        
        ///
        /// Copies the buffered render instructions to the active render instructions set.
        ///
        void ApplyBuffer();
        
        ///
        /// Performs all rendering instructions by performing rendering instructions to the
        /// web browser.
        ///
        void ExecuteInstructions() const;
        
      private:
        std::vector<ImageDrawInstruction>
        m_imageDrawInstructions; ///< Holds the image draw instructions that are executed each call to DrawCanvas().
        
        std::vector<ImageDrawInstruction>
        m_imageDrawInstructionsBuffer1; ///< Holds the buffer for the next set of draw of instructions.
        
        std::vector<ImageDrawInstruction>
        m_imageDrawInstructionsBuffer2;
        
        std::vector<ImageDrawInstruction>* m_activeBuffer {
            &m_imageDrawInstructionsBuffer1};
        std::vector<ImageDrawInstruction>* m_inactiveBuffer {
            &m_imageDrawInstructionsBuffer2};
        
        std::vector<RID> m_rids; ///< A set of preallocated RIDs used for drawing images, created in the constructor.
        
        std::vector<RID> m_ridsText;
        
        int m_ridCounterImages {0};
        
        int m_ridCounterText = {0};
        
        const int k_maxNumDrawInstructions {1000}; ///< No more images than this value can be rendererd in a single game frame.
        
        const int k_maxNumDrawTextInstructions {100}; ///< No more images than this value can be rendererd in a single game frame.
    };
}
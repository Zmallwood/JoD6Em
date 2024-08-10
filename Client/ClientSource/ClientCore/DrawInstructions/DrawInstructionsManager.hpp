/*
 * DrawInstructionsManager.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "DrawInstruction.hpp"

namespace JoD {
    
    ///
    /// Holds latest set of rendering instructions and executes them.
    ///
    class DrawInstructionsManager {
        
      public:
        ///
        /// Construct a new Draw Instructions Manager object.
        ///
        DrawInstructionsManager();
        
        ///
        /// Add new image draw instruction to group, called on request from server.
        ///
        /// @param imageNameHash Hash code of image name to draw.
        /// @param destination Destination rectangle to draw the image at.
        ///
        void AddImageDrawInstruction(int imageNameHash, BoxF destination);
        
        void AddTextDrawInstruction(std::string_view text, PointF position, bool centerAlign);
        
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
        std::vector<DrawInstruction>
        m_drawInstructionsBuffer1; ///< One of two instruction buffers.
        std::vector<DrawInstruction>
        m_drawInstructionsBuffer2; ///< One of two instruction buffers.
        std::vector<DrawInstruction>* m_activeBuffer {
            &m_drawInstructionsBuffer1}; ///< Pointer to active buffer which instructions are executed each frame.
        std::vector<DrawInstruction>* m_inactiveBuffer {
            &m_drawInstructionsBuffer2}; ///< Pointer to inactive buffer which is being populated with instructions,
        std::vector<RID> m_ridsImages; ///< A set of preallocated RIDs used for drawing images, created in the constructor.
        std::vector<RID> m_ridsText; ///< A set of preallocated RIDs used for drawing text, created in the constructor
        int m_ridCounterImages {0}; ///< Hold index for a free to use RID element in m_rids.
        int m_ridCounterText {0}; ///< Hold index for a free to use RID element in m_ridsText.
        const int k_maxNumImageDrawInstructions {6000}; ///< No more images than this value can be rendererd in a single game frame.
        const int k_maxNumTextDrawInstructions {100}; ///< No more images than this value can be rendererd in a single game frame.
    };
}
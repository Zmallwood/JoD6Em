// image_draw_instruction.h
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
//

#pragma once

namespace jod {
    //! \brief Holds data for doing a image drawing operation, created when such a request is
    //!        incoming from the server.
    struct image_draw_instruction {
        rid rid = -1; //!< ID for an image resource previously allocated.
        
        int imageNameHash = 0; //!<Hash code of image name to draw.
        
        rectf dest; //!< Destination rectangle to draw the image at.
    };
}
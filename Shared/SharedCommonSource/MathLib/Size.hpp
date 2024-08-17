/*
 * Size.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Size with int dimension.
///
struct Size {
    
    // Members
    
    int w {0};     ///< Width in int type.
    
    int h {0};     ///< Height in int type.
};

}
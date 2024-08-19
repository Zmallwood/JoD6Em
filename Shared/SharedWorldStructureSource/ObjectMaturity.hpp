/*
 * ObjectMaturity.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Available maturity stages of objects.
///
enum class ObjectMaturity {
    
    Young,   ///< Young stage of object.
    Mature,  ///< Medium aged stage of object.
    Aged     ///< Final maturity stage of object.
};

}
/*
 * CreatureMaturity.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Available maturity stages for creatures.
///
enum class CreatureMaturity {
    
    None,   ///< Unspecified maturity.
    Baby,   ///< Young creature.
    Mature, ///< Medium aged creature.
    Old     ///< Oldest stage of creature maturity.
};

}
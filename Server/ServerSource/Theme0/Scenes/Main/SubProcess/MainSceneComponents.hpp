/*
 * MainSceneComponents.h
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
/// Available scene components for MainScene.
enum class MainSceneComponents {
    CreatureTargeting, ///< Handles targeting of creatures in the world.
    MouseMovement,     ///< Handles moving by clicking with mouse.
    TileHovering,      ///< Handles hovered of the tile currently under the cursor.
    WorldView,         ///< Core game world viewing as a 2D tile grid on canvas.
    CombatMovement,    ///< Handles combat movement such as chasing targeted creature.
    Combat,
    ObjectHovering
};
}
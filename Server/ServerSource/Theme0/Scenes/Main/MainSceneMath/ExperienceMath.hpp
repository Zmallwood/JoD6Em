/*
 * ExperienceMath.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Calculates level for an actor based of its experience amount.
/// 
/// @param exp Experience of the actor.
/// @return int Calculated level.
///
int CalcCurrLevel(int exp);

///
/// Calculates experience required to achieve a certain level.
/// 
/// @param level Level to achieve.
/// @return int Required experience.
///
int CalcExpForLevel(int level);

///
/// Calculates experience difference required to get next level.
/// 
/// @param exp Actors experience.
/// @return int Experience difference.
///
int CalcExpDiffToNextLevel(int exp);

///
/// Calculates experience required to reach exactly the start of
/// the current level.
/// 
/// @param exp Current experience of actor.
/// @return int Experience required to reach current level start.
///
int CalcExpReqForCurrLevelStart(int exp);

///
/// Calculates experience gained since start of the current level.
/// 
/// @param exp Actors experience.
/// @return int Experience gained since start of current level.
///
int CalcExpGainedSinceLevelStart(int exp);

///
/// Calculates the fractional experience progress towards next level
/// in range 0.0f - 1.0f.
/// 
/// @param exp Current experience of actor.
/// @return float Fractional experience progress.
///
float CalcFractionalExpProgress(int exp);

}
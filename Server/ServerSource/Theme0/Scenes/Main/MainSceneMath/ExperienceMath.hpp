/*
 * ExperienceMath.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

int GetCurrLevel(int exp);

int GetExpForLevel(int level);

int GetExpDiffToNextLevel(int exp);

int GetExpReqForCurrLevelStart(int exp);

int GetExpGainedSinceLevelStart(int exp);

float GetFractionalExpProgress(int exp);

}
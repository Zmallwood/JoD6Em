/*
 * ExperienceMath.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

int CalcCurrLevel(int exp);

int CalcExpForLevel(int level);

int CalcExpDiffToNextLevel(int exp);

int CalcExpReqForCurrLevelStart(int exp);

int CalcExpGainedSinceLevelStart(int exp);

float CalcFractionalExpProgress(int exp);

}
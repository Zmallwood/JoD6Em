/*
 * ExperienceMath.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ExperienceMath.hpp"

namespace JoD {
int CalcCurrLevel(int exp) {
// Apply formula for level calculation.
    auto level = std::trunc(log2f(pow(exp + 70, 2) / 5000)) + 1;
    return static_cast<int>(level);
}

int CalcExpForLevel(int level) {
// Apply formula for exp calculation, inverse of the level calc formula.
    auto exp = std::max(sqrtf(powf(2, level - 1) * 5000) - 70, 0.0f);
    return static_cast<int>(exp);
}

int CalcExpDiffToNextLevel(int exp) {
    auto currLv = CalcCurrLevel(exp);
    auto nextLv = currLv + 1;
    auto totExpCurrLv = CalcExpForLevel(currLv);
    auto totExpNextLv = CalcExpForLevel(nextLv);
// Calculate the exp difference between next and current level.
    return totExpNextLv - totExpCurrLv;
}

int CalcExpReqForCurrLevelStart(int exp) {
    auto currLv = CalcCurrLevel(exp);
// Get exact exp amount required for start of current level.
    return CalcExpForLevel(currLv);
}

int CalcExpGainedSinceLevelStart(int exp) {
// Calculate difference between current exp and exp at current level start.
    return exp - CalcExpReqForCurrLevelStart(exp);
}

float CalcFractionalExpProgress(int exp) {
// Calculate exp gained since level start.
    auto xpGain = exp - CalcExpReqForCurrLevelStart(exp);
// Calculate exp required between the current and next level.
    auto xpDiff = CalcExpDiffToNextLevel(exp);
// Calculate the fractional value.
    return static_cast<float>(xpGain) / xpDiff;
}
}
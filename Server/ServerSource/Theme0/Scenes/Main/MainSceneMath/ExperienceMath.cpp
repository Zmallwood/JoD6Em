/*
 * ExperienceMath.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ExperienceMath.hpp"

namespace JoD {

int GetCurrLevel(int exp) {
    
    auto val = std::trunc(log2f(pow(exp + 70, 2) / 5000)) + 1;
    
    return static_cast<int>(val);
}

int GetExpForLevel(int level) {
    
    auto val = std::max(sqrtf(powf(2, level - 1) * 5000) - 70, 0.0f);
    
    return static_cast<int>(val);
}

int GetExpDiffToNextLevel(int exp) {
    
    auto currLv = GetCurrLevel(exp);
    auto nextLv = currLv + 1;
    auto totExpCurrLv = GetExpForLevel(currLv);
    auto totExpNextLv = GetExpForLevel(nextLv);
    
    return totExpNextLv - totExpCurrLv;
}

int GetExpReqForCurrLevelStart(int exp) {
    
    auto currLv = GetCurrLevel(exp);
    
    return GetExpForLevel(currLv);
}

int GetExpGainedSinceLevelStart(int exp) {
    
    return exp - GetExpReqForCurrLevelStart(exp);
}

float GetFractionalExpProgress(int exp) {
    
    auto xpGain = exp - GetExpReqForCurrLevelStart(exp);
    auto xpDiff = GetExpDiffToNextLevel(exp);
    
    return static_cast<float>(xpGain) / xpDiff;
}

}
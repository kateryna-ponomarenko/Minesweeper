#pragma once
#include "Difficulty.h"
class HardDifficulty :
    public Difficulty
{
public:
    HardDifficulty() : Difficulty("Hard", 30, 16, 99, 900) {}
};


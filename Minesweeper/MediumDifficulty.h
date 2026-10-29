#pragma once
#include "Difficulty.h"
class MediumDifficulty :
    public Difficulty
{
public:
    MediumDifficulty() : Difficulty("Medium", 16, 16, 40, 600) { timeMinesCount = 5; }
};


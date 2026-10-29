#pragma once
#include "Difficulty.h"
class EasyDifficulty :
    public Difficulty
{
public:
    EasyDifficulty() : Difficulty("Easy", 9, 9, 10, 300) { timeMinesCount = 2; }
};


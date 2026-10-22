#pragma once
#include "Difficulty.h"
class EasyDifficulty :
    public Difficulty
{
    EasyDifficulty() : Difficulty("Easy", 9, 9, 10, 300) {}
};


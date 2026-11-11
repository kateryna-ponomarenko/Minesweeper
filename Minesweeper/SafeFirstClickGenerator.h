#pragma once
#include "MineGenerator.h"
#include "Cell.h"
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

class SafeFirstClickGenerator :
    public MineGenerator
{
public:
	SafeFirstClickGenerator(int mines, int timeMines = 0) : MineGenerator(mines, timeMines) {}

protected:
	bool isForbidden(int x, int y, int sx, int sy) const override
	{
		return std::abs(x - sx) <= 1 && std::abs(y - sy) <= 1;
	}

};


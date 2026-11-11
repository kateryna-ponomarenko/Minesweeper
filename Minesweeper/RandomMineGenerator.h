#pragma once
#include "MineGenerator.h"
#include "Cell.h"
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

class RandomMineGenerator :
    public MineGenerator
{
public:
	RandomMineGenerator(int mines, int timeMines = 0) : MineGenerator(mines, timeMines) {}

protected:
	bool isForbidden(int x, int y, int sx, int sy) const override
	{
		return x == sx && y == sy;
	}
};


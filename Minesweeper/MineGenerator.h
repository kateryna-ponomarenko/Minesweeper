#pragma once
#include <vector>
#include "Cell.h"

//interface
class MineGenerator
{
public:
	virtual void generate(std::vector<std::vector<Cell>>& board, int safeX, int safeY) = 0;
	virtual ~MineGenerator() = default;
};


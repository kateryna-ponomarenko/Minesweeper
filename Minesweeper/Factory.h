#pragma once
#include "Board.h"
#include "Difficulty.h"
#include "RandomMineGenerator.h"
#include "SafeFirstClickGenerator.h"

class Factory
{
public:
	static Board create(const Difficulty& difficulty, MineGenerator* generator)
	{
		Board board(difficulty.getWithd(), difficulty.getHeight(), difficulty.getMinesCount());
		board.setGenerator(generator);

		return board;
	
	}
};


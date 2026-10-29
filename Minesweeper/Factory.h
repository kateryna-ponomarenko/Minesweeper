#pragma once
#include <memory>
#include "Board.h"
#include "Difficulty.h"
#include "RandomMineGenerator.h"
#include "SafeFirstClickGenerator.h"

class Factory
{
public:
	static std::unique_ptr<Board> create(const Difficulty& difficulty, bool safeFirstClick, bool timeMode)
	{
		auto board = std::make_unique<Board>(difficulty.getWidth(), difficulty.getHeight(), difficulty.getMinesCount());
		
		int mines = difficulty.getMinesCount();
		int timeMines = timeMode ? difficulty.getTimeMinesCount() : 0;

		if (safeFirstClick == true)
		{
			board->setGenerator(std::make_unique<SafeFirstClickGenerator>(mines, timeMines));
		}
		else
		{
			board->setGenerator(std::make_unique<RandomMineGenerator>(mines, timeMines));
		}

		return board;
	
	}
};


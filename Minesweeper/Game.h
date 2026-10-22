#pragma once
#include "Board.h"
#include "Timer.h"
#include "Difficulty.h"
#include "Factory.h"

class Game
{
private:
	Board board;
	Timer timer;
	Difficulty difficulty;
	bool modeTime;
	bool safeClick;
	GameState* state;


public:

	Game(Difficulty* diff, bool timed, bool safe, MineGenerator* generator)
		: board(diff->getWithd(), diff->getHeight(), diff->getMinesCount()),
		timer(diff->getLimitSeconds()),
		difficulty(diff),
		modeTime(timed),
		safeClick(safe),
		state(nullptr)
	{
		board.setGenerator(generator);
		setstate
	}


};
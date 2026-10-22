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

	Game() : difficulty(nullptr), isTimed(false), safeFirstClick(true), state(nullptr) {}
};


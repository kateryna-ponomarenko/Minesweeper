#pragma once
#include "GameStatus.h"
class Game; // forward declaration

class GameState
{
public:
	virtual void openCell(Game& game, int x, int y) = 0; //virtual
	virtual void toggleMark(Game& game, int x, int y) = 0;
	virtual void update(Game& game) = 0;
	virtual GameStatus getStatus() const = 0;

	virtual ~GameState() = default;
};


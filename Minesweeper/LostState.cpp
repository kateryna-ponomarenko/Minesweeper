#include "LostState.h"
#include "Game.h"

void LostState::update(Game& game)
{
	game.getTimer().stopTimer();
	game.getBoard().revealAllMines();
}
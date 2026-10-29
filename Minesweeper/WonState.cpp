#include "WonState.h"
#include "Game.h"

void WonState::update(Game& game)
{
    game.getTimer().stopTimer();
    game.getBoard().flagAllMines();
}
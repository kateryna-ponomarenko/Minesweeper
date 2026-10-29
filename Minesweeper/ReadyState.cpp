#include "ReadyState.h"
#include "PlayingState.h"
#include "Game.h"
#include <memory>

void ReadyState::openCell(Game& game, int x, int y) 
{
    if (!game.getBoard().isInside(x, y)) return;

    Cell& cell = game.getBoard().getCell(x, y);
    if (cell.getIsFlagged() || cell.getIsQuestioned()) return;

    game.getBoard().generateMines(x, y);
    game.getTimer().startTimer();
   
    game.setState(std::make_unique<PlayingState>());
    game.openCell(x, y);

}

void ReadyState::toggleMark(Game& game, int x, int y)  
{
    if (!game.getBoard().isInside(x, y)) return;
    game.getBoard().getCell(x, y).cycleMark();
}

void ReadyState::update(Game& game) {}
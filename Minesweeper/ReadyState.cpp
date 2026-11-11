#include "ReadyState.h"
#include "PlayingState.h"
#include "Game.h"
#include <memory>

void ReadyState::openCell(Game& game, int x, int y) 
{
    if (!game.getBoard().isInside(x, y)) return;

    auto& board = game.getBoard();

    Cell& cell = board.getCell(x, y);
    if (cell.getIsFlagged() || cell.getIsQuestioned()) return;

    board.generateMines(x, y);
    game.getTimer().startTimer();
   
    board.reveal(x, y);
    
    game.setState(std::make_unique<PlayingState>());
}

void ReadyState::toggleMark(Game& game, int x, int y)  
{
    if (!game.getBoard().isInside(x, y)) return;
    game.getBoard().getCell(x, y).cycleMark();
}

void ReadyState::update(Game& game) {}
#include "PlayingState.h"
#include "LostState.h"
#include "WonState.h"
#include "Game.h"
#include <memory>
void PlayingState::openCell(Game& game, int x, int y)
{


    auto& board = game.getBoard();
    if (!board.isInside(x, y)) return;

    auto& cell = board.getCell(x, y);


    if (cell.getIsRevealed() || cell.getIsQuestioned() || cell.getIsFlagged()) { return; }

    board.revealCell(x, y);
   
    if (cell.getHasMine())
    {
        game.setState(std::make_unique<LostState>());
        game.update(); // зупинить таймер і покаже всі міни
        return;
    }

    if (cell.getIsTimeMine())
    {
        game.getTimer().addPenalty(30);
    }

    if (cell.getNeighboringMines() == 0)
    {
        board.revealNeighbors(x, y);
    }

    if (game.checkWinCondition() == true)
    {
        game.setState(std::make_unique<WonState>());
        game.update();
    }

    
}


void PlayingState::toggleMark(Game& game, int x, int y)
{
    if (!game.getBoard().isInside(x, y)) return;
    game.getBoard().getCell(x, y).cycleMark();
}

void PlayingState::update(Game& game) 
{
    if (game.checkLoseCondition()) {
        game.setState(std::make_unique<LostState>());
        game.update(); // це зупинить гру
        return;
    }

    if (game.checkWinCondition()) {
        game.setState(std::make_unique<WonState>());
        game.update();
    }
}
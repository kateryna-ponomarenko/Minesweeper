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

    std::vector<Cell*> opened = board.reveal(x, y);

    for (Cell* c : opened)
    {
        if (c->getHasMine())
        {
            game.setState(std::make_unique<LostState>());
            game.update();
            return;
        }
        else if (c->getIsTimeMine() && game.getTimeMode())
        {
            game.getTimer().addPenalty(game.getDifficulty().getTimePenalty());
        }
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
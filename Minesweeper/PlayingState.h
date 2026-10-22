#pragma once
#include "GameState.h"
#include "Game.h"

class PlayingState :
    public GameState
{
    void openCell(Game& game, int x, int y) override;

    void toggleMark(Game& game, int x, int y) override;

    void update(Game& game) override {}
};


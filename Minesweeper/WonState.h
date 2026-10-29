#pragma once
#include "GameState.h"


class WonState :
    public GameState
{
public:
    GameStatus getStatus() const override { return GameStatus::Won; }

    void openCell(Game& game, int x, int y) override {}

    void toggleMark(Game& game, int x, int y) override {}

    void update(Game& game) override;
};


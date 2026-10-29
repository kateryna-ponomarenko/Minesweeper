#pragma once
#include "GameState.h"


class LostState :
    public GameState
{
public:
    GameStatus getStatus() const override { return GameStatus::Lost; }

    void openCell(Game& game, int x, int y) override {}

    void toggleMark(Game& game, int x, int y) override {}

    void update(Game& game) override;
};


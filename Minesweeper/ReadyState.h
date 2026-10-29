#pragma once
#include "GameState.h"

class ReadyState :
    public GameState
{
public:
	GameStatus getStatus() const override { return GameStatus::Ready; }
	void openCell(Game& game, int x, int y) override;
	void toggleMark(Game& game, int x, int y) override;
	void update(Game& game) override;
};


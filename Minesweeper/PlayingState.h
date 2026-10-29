#pragma once
#include "GameState.h"
#include "LostState.h"
#include "WonState.h"

class PlayingState :
    public GameState
{
public:
	GameStatus getStatus() const override { return GameStatus::Playing; }
	void openCell(Game& game, int x, int y) override;
	void toggleMark(Game& game, int x, int y) override;
	void update(Game& game) override;
};


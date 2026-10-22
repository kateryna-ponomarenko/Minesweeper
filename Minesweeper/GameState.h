#pragma once
class GameState
{
public:
	virtual void openCell(Game& game, int x, int y);
	virtual void toggleMark(Game& game, int x, int y);
	virtual ~GameState() = default;
	virtual void update(Game& game) = 0;

};


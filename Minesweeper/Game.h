#pragma once
#include <memory>
#include "Board.h"
#include "Timer.h"
#include "Difficulty.h"
#include "Factory.h"
#include "GameState.h"
#include "ReadyState.h"
#include "LostState.h"
#include "WonState.h"
#include "Observer.h"
#include "PlayingState.h"

class Game
{
private:
	std::unique_ptr<Board> board;
	Timer timer;
	Difficulty difficulty;
	bool modeTime;
	bool safeClick;
	std::unique_ptr<GameState> state;
	std::vector<Observer*> observers;


public:

	Game(Difficulty& diff, bool timed, bool safe)
		: board(Factory::create(diff, safe, timed)),
		timer(diff.getLimitSeconds()),
		difficulty(diff),
		modeTime(timed),
		safeClick(safe)

	{
		setState(std::make_unique<ReadyState>());
	}

	void setState(std::unique_ptr<GameState> newState)
	{
		state = std::move(newState);
		
	}

	void openCell(int x, int y)
	{
		if (state != nullptr)
		{
			state->openCell(*this, x, y); // *this спосіб передати поточний об’єкт класу у функцію
			notifyObservers();
		}
	}

	void toggleMark(int x, int y)
	{
		if (state != nullptr)
		{
			state->toggleMark(*this, x, y); 
			notifyObservers();
		}
	}

	void update()
	{
		if (state != nullptr)
		{
			state->update(*this);
		}
	}

	bool checkWinCondition()
	{ 
		int safeCellsCount = difficulty.getWidth() * difficulty.getHeight() - difficulty.getMinesCount();
		int openCellsCount = 0;

		for (int y=0; y < board->getHeight(); ++y)
			for (int x = 0; x < board->getWidth(); ++x)
			{
				auto& cell = board->getCell(x,y);// посилання на клітинку
				if (cell.getIsRevealed() && !cell.getHasMine())
				{
					++openCellsCount;
				}
			}
		return safeCellsCount == openCellsCount;
	}

	bool checkLoseCondition()
	{
		for (int y = 0; y < board->getHeight(); ++y)
			for (int x = 0; x < board->getWidth(); ++x)
			{
				auto& cell = board->getCell(x, y);// посилання на клітинку
				if (cell.getIsRevealed() && cell.getHasMine())
				{
					return true; // ;ose bc mine
				}
			}
		return modeTime && timer.isTimeUp(); // lose bc of time
	}

	void restart()
	{
		board = Factory::create(difficulty, safeClick, modeTime);
		timer.resetTimer();
		setState(std::make_unique<ReadyState>());
		notifyObservers();
	}

	void subscribe(Observer* obs)
	{
		observers.push_back(obs);

	}

	void notifyObservers()
	{
		for (Observer* obs : observers)
		{
			obs->update();
		}
	}



	Board& getBoard()
	{
		return *board;
	}

	Timer& getTimer()
	{
		return timer;
	}
	
	Difficulty& getDifficulty()
	{
		return difficulty;
	}
	
	bool getTimeMode() 
	{
		return modeTime;
	}
	
	bool getSafeFirstClick()
	{
		return safeClick;
	}

	GameStatus getStatus()
	{
		return state->getStatus();
	}

	int getMinesLeft()
	{
		int flags = 0;

			for (int y = 0; y < board->getHeight(); ++y)
				for (int x = 0; x < board->getWidth(); ++x)
				{
					if (board->getCell(x, y).getIsFlagged())
					{
						++flags;
					}
				}
			return difficulty.getMinesCount() - flags;
	}
};
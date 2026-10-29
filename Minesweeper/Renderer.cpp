#include "Renderer.h"
#include "Game.h"
#include <iostream>
#include <iomanip>

void Renderer::update()
{
	draw();
}

void Renderer::draw()
{
	Board& board = game.getBoard();

	std::cout << "\n";
	std::cout << "Mines left: " << game.getMinesLeft();
	if (game.getTimeMode() == true)
	{
		std::cout << "Time left: " << game.getTimer().getRemainingTime() << "s";
	}
	else
	{
		std::cout << "   Time: " << game.getTimer().getElapsedTime() << "s";
	}
	std::cout << "\n\n";


	std::cout << "  ";
	for (int x = 0; x < board.getWidth(); ++x)
		std::cout << std::setw(2) << x << " "; //setw(2) - встановлує ширину щоб нормально виглядало
	std::cout << "\n";

	for (int y = 0; y < board.getHeight(); ++y)
	{
		std::cout << std::setw(3) << y << " ";
		for (int x = 0; x < board.getWidth(); ++x)
		{
			Cell& cell = board.getCell(x, y);
			char symbol;

			if (cell.getIsRevealed())
			{
				if (cell.getHasMine() == true) symbol = '*';
				else if (cell.getNeighboringMines() == 0) symbol = '_';
				else if (cell.getIsTimeMine()) symbol = 'T';
				else symbol = static_cast<char>('0' + cell.getNeighboringMines());
				
			}

			else if (cell.getIsFlagged()) symbol = 'F';
			else if (cell.getIsQuestioned()) symbol = '?';
			else symbol = '#';

			std::cout << std::setw(2) << symbol << " ";

			
			
		}
		std::cout << "\n";


	}

	switch (game.getStatus())
	{
	case GameStatus::Won:
		std::cout << "*** WON ***  (r - new game, q - quit)\n";
		break;
	case GameStatus::Lost:
		std::cout << "*** LOST ***  (r - new game, q - quit)\n";
		break;
	default:
		break;
	}

	std::cout << std::endl;
}
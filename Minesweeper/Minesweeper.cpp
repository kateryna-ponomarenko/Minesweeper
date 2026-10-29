#include <iostream>
#include <string>
#include "Game.h"
#include "Renderer.h"
#include "EasyDifficulty.h"
#include "MediumDifficulty.h"
#include "HardDifficulty.h"

int main()
{
	
	std::cout << "1 - Easy, 2 - Medium, 3 - Hard\n";
	std::cout << "Choose difficulty: ";
	int level;
	std::cin >> level;

	Difficulty diff = MediumDifficulty();
	if (level == 1) diff = EasyDifficulty();
	if (level == 3) diff = HardDifficulty();

	
	char answer;
	std::cout << "Time attack mode? (y/n): ";
	std::cin >> answer;
	bool timed = (answer == 'y');

	std::cout << "Safe first click? (y/n): ";
	std::cin >> answer;
	bool safe = (answer == 'y');

	
	Game game(diff, timed, safe);
	Renderer renderer(game);
	game.subscribe(&renderer);

	std::cout << "Commands: o x y (open), f x y (flag), r (restart), q (quit)\n";
	renderer.draw();

	
	std::string cmd;
	while (true)
	{
		std::cout << "> ";
		std::cin >> cmd;

		if (cmd == "q")
		{
			break;
		}
		else if (cmd == "r")
		{
			game.restart();
		}
		else if (cmd == "o" || cmd == "f")
		{
			int x, y;
			std::cin >> x >> y;

			if (x < 0 || x >= game.getBoard().getWidth() ||
				y < 0 || y >= game.getBoard().getHeight())
			{
				std::cout << "Out of range\n";
				continue;
			}

			if (cmd == "o") game.openCell(x, y);
			else            game.toggleMark(x, y);
		}
		else
		{
			std::cout << "Unknown command\n";
		}

		if (timed) game.update();   
	}

	return 0;
}
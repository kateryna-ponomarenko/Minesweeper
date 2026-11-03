#include "SFMLRenderer.h"

SFMLRenderer::SFMLRenderer(Game& game) : game(game), window(sf::VideoMode(800, 600), "Minesweeper")
{
	
}

void  SFMLRenderer::update()
{

}

void SFMLRenderer::run()
{
	while (window.isOpen())
	{
		processEvents(); // обробка подій SFML
		game.update(); // оновлення стану гри	
		draw();
	}
}

void SFMLRenderer::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) //цикл з  pollEvent() обробляє всі події, що відбулися з моменту останнього виклику
	{
		//Close event

		if (event.type == sf::Event::Closed) //перевірка, чи була подія закриття вікна
		{
			window.close();
		}

		//mouse events
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::Right == event.mouseButton.button)
			{
				// Обробка правого кліку миші
			}
			else if (sf::Mouse::Left == event.mouseButton.button)
			{
				// Обробка лівого кліку миші
			}

		}

		//keyboard events
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::R)
			{
				// Обробка натискання клавіші R
			}
			
			else if (event.key.code == sf::Keyboard::Escape)
			{
				window.close(); // Закриття вікна при натисканні клавіші Escape
			}
			
		}

		
		

	}
}

void SFMLRenderer::draw()
{
	window.clear();
	
	drawBoard();
	drawUserInterface();

	window.display(); // Відображення вмісту вікна
}

void SFMLRenderer::drawBoard()
{

}

void SFMLRenderer::drawUserInterface()
{
}

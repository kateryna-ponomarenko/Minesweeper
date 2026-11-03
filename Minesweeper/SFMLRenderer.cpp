#include "SFMLRenderer.h"
#include "Game.h"

SFMLRenderer::SFMLRenderer(Game& game) : game(game), window(sf::VideoMode(800, 600), "Minesweeper")
{
	if (!font.loadFromFile("ITCBLKAD.TTF"))
	{
		throw std::runtime_error("Failed to load font");
	}

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
			int mouseX = event.mouseButton.x;
			int mouseY = event.mouseButton.y;

			if (mouseX >= OFFSET_X && mouseX < OFFSET_X + game.getBoard().getWidth() * CELL_SIZE &&
				mouseY >= OFFSET_Y && mouseY < OFFSET_Y + game.getBoard().getHeight() * CELL_SIZE)
			{
				int x = (mouseX - OFFSET_X) / CELL_SIZE;
				int y = (mouseY - OFFSET_Y) / CELL_SIZE;
				
				
				if (sf::Mouse::Left == event.mouseButton.button)
				{
					game.openCell(x, y); // Обробка лівого кліку миші
				}
				else if (sf::Mouse::Right == event.mouseButton.button)
				{
					game.toggleMark(x, y); // Обробка правого кліку миші
				}
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
	if (game.getStatus() == GameStatus::Won)
	{
		window.clear(sf::Color::Green);
	}
	else if (game.getStatus() == GameStatus::Lost)
	{
		window.clear(sf::Color::Red);
	}
	else
	{
		window.clear();
	}
	

	drawBoard();
	drawUserInterface();

	window.display(); // Відображення вмісту вікна
}

void SFMLRenderer::drawBoard()
{
	

	Board& board = game.getBoard();
	int boardWidth = board.getWidth();
	int boardHeight = board.getHeight();

	for (int y = 0; y < boardHeight; ++y)
	{
		for (int x = 0; x < boardWidth; ++x)
		{
			Cell& cell = board.getCell(x, y);

			//створення прямокутника для відображення клітинки
			sf::RectangleShape cellShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			
			float screenX = OFFSET_X + x * CELL_SIZE;
			float screenY = OFFSET_Y + y * CELL_SIZE;

			cellShape.setPosition(screenX, screenY);
			cellShape.setOutlineThickness(1.f); 
			cellShape.setOutlineColor(sf::Color::Black); // Встановлення кольору контуру клітинки


			if (cell.getIsRevealed())
			{

				cellShape.setFillColor(sf::Color::White); // Відображення відкритої клітинки
				window.draw(cellShape);

				if (cell.getHasMine())
				{
					//todo: відобразити міну

					cellShape.setFillColor(sf::Color::Black); // Відображення клітинки з міною
					window.draw(cellShape);

					sf::Text numberText;
					numberText.setString("*");
					numberText.setFont(font);
					numberText.setCharacterSize(24);
					numberText.setFillColor(sf::Color::Red);
					numberText.setPosition(screenX + CELL_SIZE / 4, screenY + CELL_SIZE / 8); // Встановлення позиції тексту
					window.draw(numberText);
					
					
				}


				else if (cell.getIsTimeMine())
				{
					//todo: відобразити міну

					cellShape.setFillColor(sf::Color::Blue); // Відображення клітинки з таймерною міною
					window.draw(cellShape);

					sf::Text numberText;
					numberText.setString("*");
					numberText.setFont(font);
					numberText.setCharacterSize(24);
					numberText.setFillColor(sf::Color::White);
					numberText.setPosition(screenX + CELL_SIZE / 4, screenY + CELL_SIZE / 8); // Встановлення позиції тексту
					window.draw(numberText);

				
				}

				else if (cell.getNeighboringMines() > 0)
				{


					sf::Text numberText;
					numberText.setString(std::to_string(cell.getNeighboringMines()));
					numberText.setFont(font);
					numberText.setCharacterSize(24);
					numberText.setFillColor(sf::Color::Black);
					numberText.setPosition(screenX + CELL_SIZE / 4, screenY + CELL_SIZE / 8); // Встановлення позиції тексту
					window.draw(numberText);

				}
				
			
			}
			
			else if (cell.getIsFlagged())
			{
				cellShape.setFillColor(sf::Color::Red); // Відображення клітинки з прапорцем
				window.draw(cellShape);

				sf::Text numberText;
				numberText.setString("F");
				numberText.setFont(font);
				numberText.setCharacterSize(24);
				numberText.setFillColor(sf::Color::White);
				numberText.setPosition(screenX + CELL_SIZE / 4, screenY + CELL_SIZE / 8); // Встановлення позиції тексту
				window.draw(numberText);

				
			}


			else if (cell.getIsQuestioned())
			{
				cellShape.setFillColor(sf::Color::Yellow); // Відображення клітинки з знаком питання
				window.draw(cellShape);

				sf::Text numberText;
				numberText.setString("?");
				numberText.setFont(font);
				numberText.setCharacterSize(24);
				numberText.setFillColor(sf::Color::Red);
				numberText.setPosition(screenX + CELL_SIZE / 4, screenY + CELL_SIZE / 8); // Встановлення позиції тексту
				window.draw(numberText);
				
				
			}
			

			else
			{
				cellShape.setFillColor(sf::Color::Green); 
				window.draw(cellShape);
				
			}


		}
	}

}

void SFMLRenderer::drawUserInterface()
{
	sf::Text minesText;
	minesText.setFont(font);
	minesText.setCharacterSize(20);
	minesText.setString("Mines: " + std::to_string(game.getMinesLeft()));
	minesText.setPosition(10.f, 10.f);
	minesText.setFillColor(sf::Color::White);
	window.draw(minesText);

	sf::Text timeText;
	timeText.setFont(font);
	timeText.setCharacterSize(20);
	timeText.setString("Time: " + std::to_string(game.getTimer().getRemainingTime()));
	timeText.setPosition(200.f, 10.f);
	timeText.setFillColor(sf::Color::White);
	window.draw(timeText);

	

	sf::Text statusText;
	statusText.setFont(font);
	statusText.setCharacterSize(20);
	
	std::string status = "Unknown";

	switch (game.getStatus())
	{
	case GameStatus::Ready:
		status = "Ready";
		break;

	case GameStatus::Playing:
		status = "Playing";
		break;

	case GameStatus::Won:
		status = "Won";
		break;

	case GameStatus::Lost:
		status = "Lost";
		break;
	}

	statusText.setString("Status: " + status);

	statusText.setPosition(400.f, 10.f);
	statusText.setFillColor(sf::Color::White);
	window.draw(statusText);
}


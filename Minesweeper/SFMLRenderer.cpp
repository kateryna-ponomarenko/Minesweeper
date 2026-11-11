#include "SFMLRenderer.h"
#include "Game.h"
#include "Difficulty.h"
#include "EasyDifficulty.h"
#include "MediumDifficulty.h"
#include "HardDifficulty.h"
#include <algorithm>

SFMLRenderer::SFMLRenderer(Game& game) : game(game), window(sf::VideoMode(1100, 700), "Minesweeper")
{
	if (!font.loadFromFile(("arial.ttf")))
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
			
			switch (currentScreen)
			{


			case ScreenState::Mode:
			{
				if (sf::Mouse::Left == event.mouseButton.button)
				{
					sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
					if (timeGame.getGlobalBounds().contains(mousePos))
					{
						game.setTimeMode(true);
						currentScreen = ScreenState::DifficultySelection;
					}
					else if (classicGame.getGlobalBounds().contains(mousePos))
					{
						game.setTimeMode(false);
						currentScreen = ScreenState::DifficultySelection;
					}

				}
				break;
			}
			case ScreenState::DifficultySelection:
			{
				if (sf::Mouse::Left == event.mouseButton.button)
				{
					sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
					if (EasyButton.getGlobalBounds().contains(mousePos))
					{
						game.setDifficulty(EasyDifficulty());
						currentScreen = ScreenState::safeClick;

					}
					else if (MediumButton.getGlobalBounds().contains(mousePos))
					{
						game.setDifficulty(MediumDifficulty());
						currentScreen = ScreenState::safeClick;
					}
					else if (HardButton.getGlobalBounds().contains(mousePos))
					{
						game.setDifficulty(HardDifficulty());
						currentScreen = ScreenState::safeClick;
					}


				}break;

			}

			case ScreenState::safeClick:
			{
				if (sf::Mouse::Left == event.mouseButton.button)
				{
					sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
					if (notSafeClick.getGlobalBounds().contains(mousePos))
					{
						game.setSafeFirstClick(false);
						currentScreen = ScreenState::Game;
						game.restart();
					}
					else if (safeClick.getGlobalBounds().contains(mousePos))
					{
						game.setSafeFirstClick(true);
						game.restart(); // Restart the game with the new settings
						currentScreen = ScreenState::Game;

					}
				}
				break;
			}
			case ScreenState::Game:
			{
				int mouseX = event.mouseButton.x;
				int mouseY = event.mouseButton.y;

				if (mouseX >= boardOffsetX && mouseX < boardOffsetX + game.getBoard().getWidth() * CELL_SIZE &&
					mouseY >= boardOffsetY && mouseY < boardOffsetY + game.getBoard().getHeight() * CELL_SIZE)
				{
					int x = (mouseX - boardOffsetX) / CELL_SIZE;
					int y = (mouseY - boardOffsetY) / CELL_SIZE;


					if (sf::Mouse::Left == event.mouseButton.button)
					{
						game.openCell(x, y); // Обробка лівого кліку миші
					}
					else if (sf::Mouse::Right == event.mouseButton.button)
					{
						game.toggleMark(x, y); // Обробка правого кліку миші
					}
					
				}break;
				
			}
			case ScreenState::Victory:
			{
				if (sf::Mouse::Left == event.mouseButton.button)
				{
					sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
					if (WinButton.getGlobalBounds().contains(mousePos))
					{
						currentScreen = ScreenState::MainMenu;
					}
				} break;
			}

			case ScreenState::GameOver:
			{
				if (sf::Mouse::Left == event.mouseButton.button)
				{
					sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
					if (LoseButton.getGlobalBounds().contains(mousePos))
					{
						currentScreen = ScreenState::MainMenu;
					}
				}break;

			}

			}
		}

		//keyboard events
		else if (event.type == sf::Event::KeyPressed)
		{

			if (event.key.code == sf::Keyboard::Enter)
			{
				if (currentScreen == ScreenState::MainMenu)
				{
					currentScreen = ScreenState::Mode;
				}
				
				else if (game.getStatus() == GameStatus::Won)
				{
					currentScreen = ScreenState::Victory;
				}
				else if (game.getStatus() == GameStatus::Lost)
				{
					currentScreen = ScreenState::GameOver;
				}
				
			}

			else if (event.key.code == sf::Keyboard::R)
			{
				game.restart();
				currentScreen = ScreenState::Game;

			}
			
			else if (event.key.code == sf::Keyboard::Escape)
			{
				window.close(); 
			}
			
		}

		
		

	}
}

void SFMLRenderer::draw()
{
	window.clear(sf::Color::Cyan); // Очистка вікна з кольором фону

	switch (currentScreen)
	{
	case ScreenState::MainMenu:
		drawMainMenu();
		break;
	case ScreenState::Mode:
		drawModeSelectionScreen();
		break;
	case ScreenState::DifficultySelection:
		drawDifficultySelectionScreen();
		break;
	case ScreenState::safeClick:
		drawSafeClickSelectionScreen();
		break;

	case ScreenState::Game:
		drawBoard();
		drawUserInterface();
		
		break;

	case ScreenState::Victory:
		drawVictoryScreen();
		break;	

	case ScreenState::GameOver:
		drawGameOverScreen();
		break;

	}
	window.display();


	
}

void SFMLRenderer::drawBoard()
{
	

	Board& board = game.getBoard();

	float boardWidthInPixels = board.getWidth() * CELL_SIZE;
	boardOffsetX = (window.getSize().x - boardWidthInPixels) / 2.f; // Центрування ігрового поля по горизонталі
	boardOffsetY = (window.getSize().y - board.getHeight() * CELL_SIZE) / 2.f; // Центрування ігрового поля по вертикалі

	int boardWidth = board.getWidth();
	int boardHeight = board.getHeight();

	//frame
	float boardWidthPixels = board.getWidth() * CELL_SIZE;
	float boardHeightPixels = board.getHeight() * CELL_SIZE;

	const float FRAME_PADDING_X = 40.f;
	const float FRAME_PADDING_Y = 20.f;

	sf::RectangleShape frame(
		sf::Vector2f(
			boardWidthPixels + FRAME_PADDING_X * 2,
			boardHeightPixels + FRAME_PADDING_Y * 2
		)
	);

	frame.setPosition(
		boardOffsetX - FRAME_PADDING_X,
		boardOffsetY - FRAME_PADDING_Y
	);
	
	
	frame.setFillColor(sf::Color::Transparent);
	frame.setOutlineThickness(3.f);
	frame.setOutlineColor(sf::Color::White);
	window.draw(frame);



	for (int y = 0; y < boardHeight; ++y)
	{
		for (int x = 0; x < boardWidth; ++x)
		{
			Cell& cell = board.getCell(x, y);

			//створення прямокутника для відображення клітинки
			sf::RectangleShape cellShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
		

			float screenX = boardOffsetX + x * CELL_SIZE;
			float screenY = boardOffsetY + y * CELL_SIZE;

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
					// Встановлення позиції тексту
					sf::FloatRect bounds = cellShape.getGlobalBounds();
					//FloatRect is struct that defines a rectangle by its position and size. It has members left, top, width, and height.
					//getLocalBounds() is a method that returns the local bounding rectangle of the text,
					numberText.setPosition(
						screenX + (CELL_SIZE - numberText.getLocalBounds().width) / 2.f,
						screenY + (CELL_SIZE - numberText.getLocalBounds().height) / 2.f //через відступи 
					);


					window.draw(numberText);
					
					
				}


				else if (cell.getIsTimeMine())
				{
					//todo: відобразити міну

					cellShape.setFillColor(sf::Color::Blue); // Відображення клітинки з таймерною міною
					window.draw(cellShape);

					sf::Text numberText;
					
					numberText.setFont(font);
					numberText.setCharacterSize(24);
					numberText.setFillColor(sf::Color::White);
					int n = cell.getNeighboringMines();
					numberText.setString(n > 0 ? std::to_string(n) : "T");
					// Встановлення позиції тексту
					sf::FloatRect bounds = cellShape.getGlobalBounds();
					numberText.setPosition(
						screenX + (CELL_SIZE - numberText.getLocalBounds().width) / 2.f,
						screenY + (CELL_SIZE - numberText.getLocalBounds().height) / 2.f //через відступи 
					);
					window.draw(numberText);

				
				}

				else if (cell.getNeighboringMines() > 0)
				{


					sf::Text numberText;
					numberText.setString(std::to_string(cell.getNeighboringMines()));
					numberText.setFont(font);
					numberText.setCharacterSize(24);
					numberText.setFillColor(sf::Color::Black);
					// Встановлення позиції тексту
					sf::FloatRect bounds = cellShape.getGlobalBounds();
					numberText.setPosition(
						screenX + (CELL_SIZE - numberText.getLocalBounds().width) / 2.f,
						screenY + (CELL_SIZE - numberText.getLocalBounds().height) / 2.f //через відступи 
					);
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
				// Встановлення позиції тексту
				sf::FloatRect bounds = cellShape.getGlobalBounds();
				numberText.setPosition(
					screenX + (CELL_SIZE - numberText.getLocalBounds().width) / 2.f,
					screenY + (CELL_SIZE - numberText.getLocalBounds().height) / 2.f //через відступи 
				);
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
				// Встановлення позиції тексту
				sf::FloatRect bounds = cellShape.getGlobalBounds();
				numberText.setPosition(
					screenX + (CELL_SIZE - numberText.getLocalBounds().width) / 2.f,
					screenY + (CELL_SIZE - numberText.getLocalBounds().height) / 2.f //через відступи 
				);
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
	Board& board = game.getBoard();
	float windowWidth = window.getSize().x;


	// Відображення кількості мін, що залишилися

	sf::Text minesText;
	minesText.setFont(font);
	minesText.setCharacterSize(20);
	minesText.setString("Mines: " + std::to_string(game.getMinesLeft()));
	
	//centring
	
	minesText.setPosition(50.f,50.f);

	minesText.setFillColor(sf::Color::White);
	window.draw(minesText);


	// Відображення таймера гри
	int shown;
	std::string label;

	if (game.getTimeMode())
	{
		shown = game.getTimer().getRemainingTime();
		label = "Time left: ";
	}
	else
	{
		shown = std::min(game.getTimer().getElapsedTime(), 999);   // класика: вгору, максимум 999
		label = "Time: ";
	}


	sf::Text timeText;
	timeText.setFont(font);
	timeText.setCharacterSize(20);

	timeText.setString(label + std::to_string(shown));
	
	//centring
	sf::FloatRect timeBounds =
		timeText.getLocalBounds();
	timeText.setPosition(windowWidth - timeBounds.width - 50.f,50.f);

	timeText.setFillColor(sf::Color::White);
	window.draw(timeText);

	
	// Відображення статусу гри

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

	//centring
	sf::FloatRect statusBounds =
		statusText.getLocalBounds();
	statusText.setPosition((windowWidth - statusBounds.width) / 2.f, 50.f);

	statusText.setFillColor(sf::Color::White);
	window.draw(statusText);
}

void SFMLRenderer::drawMainMenu()
{
	// Clear the window with a background color
	window.clear(sf::Color::Cyan);
	
	// Draw the main menu text
	sf::Text titleText;
	titleText.setFont(font);
	titleText.setCharacterSize(48);
	titleText.setString("Minesweeper");
	titleText.setFillColor(sf::Color::White);
	
	// Center the title text
	sf::FloatRect titleBounds = titleText.getLocalBounds();
	titleText.setPosition(
		(window.getSize().x - titleBounds.width) / 2.f,100.f );
	window.draw(titleText);
	
	
	// Draw instructions or buttons for starting the game
	sf::Text instructionText;
	instructionText.setFont(font);
	instructionText.setCharacterSize(24);
	instructionText.setString("Press Enter to Start");
	instructionText.setFillColor(sf::Color::White);
	
	// Center the instruction text
	sf::FloatRect instructionBounds = instructionText.getLocalBounds();
	instructionText.setPosition(
		(window.getSize().x - instructionBounds.width) / 2.f,
		300.f // Position it below the title
	);
	window.draw(instructionText);
	
}

void  SFMLRenderer::drawModeSelectionScreen()
{
	// Clear the window with a background color
	window.clear(sf::Color::Cyan);
	
	// Draw the mode selection text
	sf::Text modeText;
	modeText.setFont(font);
	modeText.setCharacterSize(48);
	modeText.setString("Select Mode");
	modeText.setFillColor(sf::Color::White);
	
	// Center the mode text
	sf::FloatRect modeBounds = modeText.getLocalBounds();
	modeText.setPosition(
		(window.getSize().x - modeBounds.width) / 2.f, 100.f);
	window.draw(modeText);
	
	// Draw buttons for selecting the mode
	timeGame.setSize(sf::Vector2f(200.f, 50.f));
	timeGame.setFillColor(sf::Color::White);
	timeGame.setPosition((window.getSize().x - timeGame.getSize().x) / 2.f, 200.f);
	
	sf::Text timeButtonText;
	timeButtonText.setFont(font);
	timeButtonText.setCharacterSize(24);
	timeButtonText.setString("Time Attack!");
	timeButtonText.setFillColor(sf::Color::Magenta);

	// Center the button text
	sf::FloatRect timeButtonBounds = timeButtonText.getLocalBounds();
	timeButtonText.setPosition(
		timeGame.getPosition().x + (timeGame.getSize().x - timeButtonBounds.width) / 2.f,
		timeGame.getPosition().y + (timeGame.getSize().y - timeButtonBounds.height) / 2.f
	);

	classicGame.setSize(sf::Vector2f(200.f, 50.f));
	classicGame.setFillColor(sf::Color::White);
	classicGame.setPosition((window.getSize().x - classicGame.getSize().x) / 2.f, 300.f);
	
	sf::Text classicButtonText;
	classicButtonText.setFont(font);
	classicButtonText.setCharacterSize(24);
	classicButtonText.setString("Classic game");
	classicButtonText.setFillColor(sf::Color::Magenta);

	// Center the button text
	sf::FloatRect classicButtonBounds = classicButtonText.getLocalBounds();
	classicButtonText.setPosition(
		classicGame.getPosition().x + (classicGame.getSize().x - classicButtonBounds.width) / 2.f,
		classicGame.getPosition().y + (classicGame.getSize().y - classicButtonBounds.height) / 2.f
	);

	window.draw(timeGame);
	window.draw(timeButtonText);
	window.draw(classicGame);
	window.draw(classicButtonText);
	window.draw(modeText);


}

void SFMLRenderer::drawDifficultySelectionScreen()
{
	// Clear the window with a background color
	window.clear(sf::Color::Cyan);
	// Draw the difficulty selection text
	sf::Text difficultyText;
	difficultyText.setFont(font);
	difficultyText.setCharacterSize(48);
	difficultyText.setString("Select Difficulty");
	difficultyText.setFillColor(sf::Color::White);
	// Center the difficulty text
	sf::FloatRect difficultyBounds = difficultyText.getLocalBounds();
	difficultyText.setPosition(
		(window.getSize().x - difficultyBounds.width) / 2.f, 100.f);
	window.draw(difficultyText);
	
	
	// Draw buttons for selecting the difficulty
	EasyButton.setSize(sf::Vector2f(200.f, 50.f));
	EasyButton.setFillColor(sf::Color::White);
	EasyButton.setPosition((window.getSize().x - EasyButton.getSize().x) / 2.f, 200.f);
	
	sf::Text easyButtonText;
	easyButtonText.setFont(font);
	easyButtonText.setCharacterSize(24);
	easyButtonText.setString("Easy");
	easyButtonText.setFillColor(sf::Color::Green);
	// Center the button text
	sf::FloatRect easyButtonBounds = easyButtonText.getLocalBounds();
	easyButtonText.setPosition(
		EasyButton.getPosition().x + (EasyButton.getSize().x - easyButtonBounds.width) / 2.f,
		EasyButton.getPosition().y + (EasyButton.getSize().y - easyButtonBounds.height) / 2.f
	);


	MediumButton.setSize(sf::Vector2f(200.f, 50.f));
	MediumButton.setFillColor(sf::Color::White);
	MediumButton.setPosition((window.getSize().x - MediumButton.getSize().x) / 2.f, 260.f);

	sf::Text mediumButtonText;
	mediumButtonText.setFont(font);
	mediumButtonText.setCharacterSize(24);
	mediumButtonText.setString("Medium");
	mediumButtonText.setFillColor(sf::Color::Yellow);
	// Center the button text
	sf::FloatRect mediumButtonBounds = mediumButtonText.getLocalBounds();
	mediumButtonText.setPosition(
		MediumButton.getPosition().x + (MediumButton.getSize().x - mediumButtonBounds.width) / 2.f,
		MediumButton.getPosition().y + (MediumButton.getSize().y - mediumButtonBounds.height) / 2.f
	);



	HardButton.setSize(sf::Vector2f(200.f, 50.f));
	HardButton.setFillColor(sf::Color::White);
	HardButton.setPosition((window.getSize().x - HardButton.getSize().x) / 2.f, 320.f);

	sf::Text hardButtonText;
	hardButtonText.setFont(font);
	hardButtonText.setCharacterSize(24);
	hardButtonText.setString("Hard");
	hardButtonText.setFillColor(sf::Color::Red);
	// Center the button text
	sf::FloatRect hardButtonBounds = hardButtonText.getLocalBounds();
	hardButtonText.setPosition(
		HardButton.getPosition().x + (HardButton.getSize().x - hardButtonBounds.width) / 2.f,
		HardButton.getPosition().y + (HardButton.getSize().y - hardButtonBounds.height) / 2.f
	);

	window.draw(EasyButton);
	window.draw(easyButtonText);
	window.draw(MediumButton);
	window.draw(mediumButtonText);
	window.draw(HardButton);
	window.draw(hardButtonText);
	
	
}

void SFMLRenderer::drawSafeClickSelectionScreen()
{
	// Clear the window with a background color
	window.clear(sf::Color::Cyan);

	// Draw the mode selection text
	sf::Text modeText;
	modeText.setFont(font);
	modeText.setCharacterSize(48);
	modeText.setString("Select Safe Click");
	modeText.setFillColor(sf::Color::White);

	// Center the mode text
	sf::FloatRect modeBounds = modeText.getLocalBounds();
	modeText.setPosition(
		(window.getSize().x - modeBounds.width) / 2.f, 100.f);
	window.draw(modeText);

	// Draw buttons for selecting the mode
	safeClick.setSize(sf::Vector2f(200.f, 50.f));
	safeClick.setFillColor(sf::Color::White);
	safeClick.setPosition((window.getSize().x - safeClick.getSize().x) / 2.f, 200.f);

	sf::Text safeClickButtonText;
	safeClickButtonText.setFont(font);
	safeClickButtonText.setCharacterSize(24);
	safeClickButtonText.setString("Safe Click");
	safeClickButtonText.setFillColor(sf::Color::Magenta);

	// Center the button text
	sf::FloatRect safeClickButtonBounds = safeClickButtonText.getLocalBounds();
	safeClickButtonText.setPosition(
		safeClick.getPosition().x + (safeClick.getSize().x - safeClickButtonBounds.width) / 2.f,
		safeClick.getPosition().y + (safeClick.getSize().y - safeClickButtonBounds.height) / 2.f
	);

	notSafeClick.setSize(sf::Vector2f(200.f, 50.f));
	notSafeClick.setFillColor(sf::Color::White);
	notSafeClick.setPosition((window.getSize().x - notSafeClick.getSize().x) / 2.f, 300.f);

	sf::Text notSafeClickButtonText;
	notSafeClickButtonText.setFont(font);
	notSafeClickButtonText.setCharacterSize(24);
	notSafeClickButtonText.setString("Not Safe Click");
	notSafeClickButtonText.setFillColor(sf::Color::Magenta);

	// Center the button text
	sf::FloatRect notSafeClickButtonBounds = notSafeClickButtonText.getLocalBounds();
	notSafeClickButtonText.setPosition(
		notSafeClick.getPosition().x + (notSafeClick.getSize().x - notSafeClickButtonBounds.width) / 2.f,
		notSafeClick.getPosition().y + (notSafeClick.getSize().y - notSafeClickButtonBounds.height) / 2.f
	);

	window.draw(safeClick);
	window.draw(safeClickButtonText);
	window.draw(notSafeClick);
	window.draw(notSafeClickButtonText);
	window.draw(modeText);

	

}

void SFMLRenderer::drawVictoryScreen()
{
	
	window.clear();

	sf::RectangleShape topPart(sf::Vector2f(window.getSize().x,window.getSize().y / 2.f));
	
	topPart.setFillColor(sf::Color(0, 87, 183));
	topPart.setPosition(0.f, 0.f);

	window.draw(topPart);

	sf::RectangleShape bottomPart(sf::Vector2f(window.getSize().x,window.getSize().y / 2.f));
	bottomPart.setFillColor(sf::Color(255, 215, 0)
	);
	bottomPart.setPosition(0.f,window.getSize().y / 2.f);
	window.draw(bottomPart);

	WinButton.setSize(sf::Vector2f(200.f, 50.f));
	WinButton.setFillColor(sf::Color::White);
	WinButton.setPosition((window.getSize().x - WinButton.getSize().x) / 2.f, 200.f);

	
	sf::Text victoryText;
	victoryText.setFont(font);
	victoryText.setCharacterSize(30);
	victoryText.setString("Victory!");
	victoryText.setFillColor(sf::Color::Blue);

	victoryText.setPosition(
		(WinButton.getPosition().x + (WinButton.getSize().x - victoryText.getLocalBounds().width) / 2.f),
		(WinButton.getPosition().y + (WinButton.getSize().y - victoryText.getLocalBounds().height) / 2.f)
	);

	sf::Text restartText;
	restartText.setFont(font);
	restartText.setCharacterSize(24);
	restartText.setString("Press R to Restart or click the button to go back to the main menu");
	restartText.setFillColor(sf::Color::White);
	restartText.setPosition(
		(window.getSize().x - restartText.getLocalBounds().width) / 2.f,
		300.f
	);
	
	window.draw(WinButton);
	window.draw(victoryText);
	window.draw(restartText);
	
}

void SFMLRenderer::drawGameOverScreen()
{
	
	window.clear(sf::Color::Black);

	LoseButton.setSize(sf::Vector2f(200.f, 100.f));
	LoseButton.setFillColor(sf::Color::Red);
	LoseButton.setPosition((window.getSize().x - LoseButton.getSize().x) / 2.f, 200.f);
	
	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(30);
	gameOverText.setString("Game Over!");
	gameOverText.setFillColor(sf::Color::White);

	
	// Center the game over text
	gameOverText.setPosition(
		LoseButton.getPosition().x + (LoseButton.getSize().x - gameOverText.getLocalBounds().width) / 2.f,
		LoseButton.getPosition().y + (LoseButton.getSize().y - gameOverText.getLocalBounds().height) / 2.f
	);

	sf::Text restartText;
	restartText.setFont(font);
	restartText.setCharacterSize(24);
	restartText.setString("Press R to Restart or click the button to go back to the main menu");
	restartText.setFillColor(sf::Color::White);
	restartText.setPosition(
		(window.getSize().x - restartText.getLocalBounds().width) / 2.f,
		300.f
	);

	window.draw(LoseButton);
	window.draw(gameOverText);
	window.draw(restartText);
	
}
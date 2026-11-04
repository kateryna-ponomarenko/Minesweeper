#pragma once
#include "Observer.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "ScreenState.h"


class SFMLRenderer :
    public Observer
{
private:
	Game& game;
	sf::RenderWindow window; //об'єкт вікна SFML
	sf::Font font;
	ScreenState currentScreen = ScreenState::MainMenu;

	sf::RectangleShape timeGame;
	sf::RectangleShape classicGame;

	sf::RectangleShape notSafeClick;
	sf::RectangleShape safeClick;

	sf::RectangleShape LoseButton;
	sf::RectangleShape WinButton;

	sf::RectangleShape EasyButton;
	sf::RectangleShape MediumButton;
	sf::RectangleShape HardButton;
	
	static constexpr float CELL_SIZE = 32.f; // Розмір однієї клітинки ігрового поля
	float boardOffsetX = 20.f;
	float boardOffsetY = 60.f; // Зсув для розташування ігрового поля на екрані

public:

	SFMLRenderer(Game& game);

	void update() override; // реалізація методу update() з інтерфейсу Observer
	void run();
	void processEvents(); // метод для обробки подій SFML
	void draw(); // метод для відображення гри на екрані
	void drawBoard();// метод для відображення ігрового поля
	void drawUserInterface(); // метод для відображення елементів користувацького інтерфейсу

	void drawMainMenu();
	void drawGameScreen();
	void drawVictoryScreen();
	void drawGameOverScreen();
	void drawModeSelectionScreen();
	void drawDifficultySelectionScreen();
	void drawSafeClickSelectionScreen();
};


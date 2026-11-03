#pragma once
#include "Observer.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Cell.h"


class SFMLRenderer :
    public Observer
{
private:
	Game& game;
	sf::RenderWindow window; //об'єкт вікна SFML
	sf::Font font;

	//static constexpr - одна спільна константа для всіх об'єктів.
	static constexpr float CELL_SIZE = 32.f; // Розмір однієї клітинки ігрового поля
	static constexpr float OFFSET_X = 20.f;
	static constexpr float OFFSET_Y = 60.f; // Зсув для розташування ігрового поля на екрані

public:

	SFMLRenderer(Game& game);

	void update() override; // реалізація методу update() з інтерфейсу Observer
	void run();
	void processEvents(); // метод для обробки подій SFML
	void draw(); // метод для відображення гри на екрані
	void drawBoard();// метод для відображення ігрового поля
	void drawUserInterface(); // метод для відображення елементів користувацького інтерфейсу

	

};


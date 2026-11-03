#pragma once
#include "Observer.h"
#include "Game.h"
#include <SFML/Graphics.hpp>


class SFMLRenderer :
    public Observer
{
private:
	Game& game;
	sf::RenderWindow window; //об'єкт вікна SFML

public:

	SFMLRenderer(Game& game);

	void update() override; // реалізація методу update() з інтерфейсу Observer
	void run();
	void processEvents(); // метод для обробки подій SFML
	void draw(); // метод для відображення гри на екрані
	void drawBoard(); // метод для відображення ігрового поля
	void drawUserInterface(); // метод для відображення елементів користувацького інтерфейсу
};


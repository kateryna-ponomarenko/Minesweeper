#include <iostream>
#include <string>
#include "Game.h"
#include "Renderer.h"
#include "EasyDifficulty.h"
#include "MediumDifficulty.h"
#include "HardDifficulty.h"
#include <SFML/Graphics.hpp>



int main()
{
    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "Minesweeper"
    );

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}
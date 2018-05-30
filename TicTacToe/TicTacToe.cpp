// TicTacToe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


int main()
{
	sf::RenderWindow gameWindow{ sf::VideoMode{1280, 720}, "TicTacToe" };		// Initializing main game window with resolution 1280x720 (HD)
	gameWindow.setFramerateLimit(60);											// Setting FPS limit to 60

	while (true)
	{
		gameWindow.clear(sf::Color::Blue);

		gameWindow.display();
	}

    return 0;
}


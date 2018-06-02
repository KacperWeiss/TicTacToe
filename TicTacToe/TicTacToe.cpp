// TicTacToe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Menu.h"
#include "Options.h"

enum WindowState
{
	MenuWindow, PlayWindow, OptionsWindow
};

int main()
{
	WindowState currentWindowState;
	currentWindowState = WindowState::MenuWindow;

	sf::RenderWindow gameWindow{ sf::VideoMode{1280, 720}, "TicTacToe" };		// Initializing main game window with resolution 1280x720 (HD)
	gameWindow.setFramerateLimit(60);											// Setting FPS limit to 60

	Menu menu(gameWindow.getSize().x, gameWindow.getSize().y);
	Options options(gameWindow.getSize().x, gameWindow.getSize().y);

	sf::Event event;

	while (gameWindow.isOpen())
	{
		while (gameWindow.pollEvent(event)) 
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0: // Play
						currentWindowState = WindowState::PlayWindow;
						break;
					case 1: // Options
						currentWindowState = WindowState::OptionsWindow;
						break;
					case 2: // Exit
						gameWindow.close();
						break;
					}
				}

				break;

			case  sf::Event::Closed:
				gameWindow.close();
				break;
			}
		}

		gameWindow.clear(sf::Color::Black);

		switch (currentWindowState)
		{
		case MenuWindow:
			menu.Draw(gameWindow);
			break;
		case PlayWindow:
			break;
		case OptionsWindow:
			options.Draw(gameWindow);
			break;
		}

		gameWindow.display();
	}

    return 0;
}


// TicTacToe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "Menu.h"
#include "Options.h"
#include "Game.h"
#include "GameLogic.h"
#include "PlayerAI.h"

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
	Game game(gameWindow.getSize().x, gameWindow.getSize().y, options.GetBoardSize(), options.GetWinningRow());
	GameLogic gameLogic;
	PlayerAI playerAI;

	sf::Event event;

	while (gameWindow.isOpen())
	{
		switch (currentWindowState)
		{
		case MenuWindow:
			while (gameWindow.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Q:
						gameWindow.close();
						break;

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
			break;
		case PlayWindow:
			game.Reconfigure(gameWindow.getSize().x, gameWindow.getSize().y, options.GetBoardSize(), options.GetWinningRow());
			while (currentWindowState == WindowState::PlayWindow)
			{
				while (gameWindow.pollEvent(event))
				{
					if (game.GetCurrentPlayer() == Player::O && game.CheckWin() == 0)
					{
						gameLogic.init(options.GetBoardSize(), options.GetWinningRow(), game.GetBoard(), game.GetCurrentPlayer());
						playerAI.placeMark(&game, &gameLogic, options.GetDifficulty());
					}

					switch (event.type)
					{
					case sf::Event::MouseButtonPressed:
						game.DetectMouseClick(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y);
						break;

					case sf::Event::KeyReleased:
						switch (event.key.code)
						{
						case sf::Keyboard::Escape:
							currentWindowState = WindowState::MenuWindow;
							break;

						case sf::Keyboard::Q:
							gameWindow.close();
							break;

						case sf::Keyboard::R:
							game.Reconfigure(gameWindow.getSize().x, gameWindow.getSize().y, options.GetBoardSize(), options.GetWinningRow());
							break;
						}

						break;
					case  sf::Event::Closed:
						gameWindow.close();
						break;
					}
				}

				gameWindow.clear(sf::Color::Black);

				game.Draw(gameWindow);

				gameWindow.display();
			}
			break;
		case OptionsWindow:
			while (gameWindow.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Escape:
						currentWindowState = WindowState::MenuWindow;
						break;

					case sf::Keyboard::Q:
						gameWindow.close();
						break;

					case sf::Keyboard::Up:
						options.MoveUp();
						break;

					case sf::Keyboard::Down:
						options.MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (options.GetSelectedItem())
						{
						case 0: // Board size
							options.ChangeState();
							break;
						case 1: // Winning row size
							options.ChangeState();
							break;
						case 2: // Difficulty
							options.ChangeState();
							break;
						case 3: // Back
							currentWindowState = WindowState::MenuWindow;
							break;
						}
					}

					break;

				case  sf::Event::Closed:
					gameWindow.close();
					break;
				}
			}
			break;
		default:
			break;
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


#include "stdafx.h"
#include "Game.h"


Game::Game(float width, float height, int size, int winingRow)
{
	_size = size;
	_winningRowLength = winingRow;

	_board = new int* [size];
	for (int i = 0; i < size; i++)
	{
		_board[i] = new int[size];
	}
}

Game::~Game()
{
	for (int i = 0; i < _size; i++) {
		delete[] _board[i];
	}
	delete[] _board;
}

void Game::Reconfigure(float width, float height, int size, int winingRow)
{
	// Deleting old board array
	for (int i = 0; i < _size; i++) {
		delete[] _board[i];
	}
	delete[] _board;

	_size = size;
	_winningRowLength = winingRow;

	// Recreation of board array
	_board = new int*[size];
	for (int i = 0; i < size; i++)
	{
		_board[i] = new int[size];
	}

	boardInsideLines = new sf::RectangleShape[2 * (size - 1)];

	for (int i = 0; i < size - 1; i++)
	{
		boardInsideLines[i].setSize(sf::Vector2f{ height - 32, 2 });
		boardInsideLines[i].setPosition(sf::Vector2f{ 16 + (height / size) * (i + 1), 20 });
		boardInsideLines[i].setFillColor(sf::Color::White);
		boardInsideLines[i].setRotation(90);
	}
	for (int i = 0; i < size - 1; i++)
	{
		boardInsideLines[i + size - 1].setSize(sf::Vector2f{ height - 32, 2 });
		boardInsideLines[i + size - 1].setPosition(sf::Vector2f{ 20, 16 + (height / size) * (i + 1) });
		boardInsideLines[i + size - 1].setFillColor(sf::Color::White);
	}

	// Linie wewenêtrzne i zewnêtrzne mo¿na zmieniæ w celu poprawienia ich wygl¹du
	boardOutline[0].setSize(sf::Vector2f{ height - 32, 4 });
	boardOutline[0].setPosition(sf::Vector2f{ 16, 16 });
	boardOutline[0].setFillColor(sf::Color::White);

	boardOutline[1].setSize(sf::Vector2f{ height - 32, 4 });
	boardOutline[1].setPosition(sf::Vector2f{ 20, 16 });
	boardOutline[1].setRotation(90);
	boardOutline[1].setFillColor(sf::Color::White);

	boardOutline[2].setSize(sf::Vector2f{ height - 32, 4 });
	boardOutline[2].setPosition(sf::Vector2f{ height - 12, 16 });
	boardOutline[2].setRotation(90);
	boardOutline[2].setFillColor(sf::Color::White);

	boardOutline[3].setSize(sf::Vector2f{ height - 28, 4 });
	boardOutline[3].setPosition(sf::Vector2f{ 16, height - 16 });
	boardOutline[3].setFillColor(sf::Color::White);
}

void Game::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_SIDES; i++)
	{
		window.draw(boardOutline[i]);
	}
	for (int i = 0; i < (2 * (_size - 1)); i++)
	{
		window.draw(boardInsideLines[i]);
	}
}
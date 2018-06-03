#include "stdafx.h"
#include "Game.h"


Game::Game(float width, float height, int size, int winingRow)
{
	if (!font.loadFromFile("ComicSansMS3.ttf"))
	{
		// error handling (will be done in future)
	}
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(1.0);
	text.setOutlineColor(sf::Color::White);
	text.setString("Current player: X ");
	text.setPosition(sf::Vector2f(height + 60.0, 40.0));

	_size = size;
	_winningRowLength = winingRow;
	currentPlayer = Player::X;
	whoWon = 0;

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
	text.setFillColor(sf::Color::White);
	text.setString("Current player: X ");
	text.setPosition(sf::Vector2f(height + 60.0, 40.0));

	currentPlayer = Player::X;
	whoWon = 0;

	// Deleting crosses
	crossShapes.clear();
	cirkleShapes.clear();

	// Deleting old board array
	for (int i = 0; i < _size; i++) {
		delete[] _board[i];
	}
	delete[] _board;

	_size = size;
	_winningRowLength = winingRow;

	oneSquareHeight = ((height - 40) / size);

	// Recreation of board array
	_board = new int*[size];
	for (int i = 0; i < size; i++)
	{
		_board[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			_board[i][j] = 0;
		}
	}

	boardInsideLines = new sf::RectangleShape[2 * (size - 1)];

	for (int i = 0; i < size - 1; i++)
	{
		boardInsideLines[i].setSize(sf::Vector2f{ height - 32, 2 });
		boardInsideLines[i].setPosition(sf::Vector2f{ 20 + oneSquareHeight * (i + 1), 20 });
		boardInsideLines[i].setFillColor(sf::Color::White);
		boardInsideLines[i].setRotation(90);
	}
	for (int i = 0; i < size - 1; i++)
	{
		boardInsideLines[i + size - 1].setSize(sf::Vector2f{ height - 32, 2 });
		boardInsideLines[i + size - 1].setPosition(sf::Vector2f{ 20, 20 + oneSquareHeight * (i + 1) });
		boardInsideLines[i + size - 1].setFillColor(sf::Color::White);
	}

	boardOutline.setSize(sf::Vector2f{ height - 32, height - 32 });
	boardOutline.setPosition(sf::Vector2f{ 20, 20 });
	boardOutline.setFillColor(sf::Color::Transparent);
	boardOutline.setOutlineColor(sf::Color::White);
	boardOutline.setOutlineThickness(4.0);
}

void Game::Draw(sf::RenderWindow &window)
{
	window.draw(boardOutline);
	window.draw(text);

	for (int i = 0; i < (2 * (_size - 1)); i++)
	{
		window.draw(boardInsideLines[i]);
	}

	for (int i = 0; i < crossShapes.size(); i++)
	{
		window.draw(crossShapes[i]);
	}

	for (int i = 0; i < cirkleShapes.size(); i++)
	{
		window.draw(cirkleShapes[i]);
	}
}

void Game::switchPlayer()
{
	if (currentPlayer == Player::O)
	{
		currentPlayer = Player::X;
	}
	else
	{
		currentPlayer = Player::O;
	}
}

void Game::DetectMouseClick(int x, int y)
{
	switch (currentPlayer)
	{
	case X: // Human player
		boardCoordinatesX = ((x - 20) / oneSquareHeight);
		boardCoordinatesY = ((y - 20) / oneSquareHeight);

		if (boardCoordinatesX >= 0 && boardCoordinatesX < _size && boardCoordinatesY >= 0 && boardCoordinatesY < _size)
		{
			if (_board[boardCoordinatesX][boardCoordinatesY] == 0)
			{
				if (whoWon != 0)
				{
					return;
				}
				_board[boardCoordinatesX][boardCoordinatesY] = 1;
				CrossShape cross(20 + boardCoordinatesX * oneSquareHeight, 20 + boardCoordinatesY * oneSquareHeight, oneSquareHeight);
				crossShapes.push_back(cross);
				if (CheckWin(boardCoordinatesX, boardCoordinatesY) == 1)
				{
					text.setFillColor(sf::Color::Green);
					text.setString("Player X won! \n Press \'R\' to restart, \n or escape to go back!");
					return;
				}
				else if(CheckWin(boardCoordinatesX, boardCoordinatesY) == -1)
				{
					text.setFillColor(sf::Color::Yellow);
					text.setString("Draw! \n Press \'R\' to restart, \n or escape to go back!");
					return;
				}
				
				text.setString("Current player: O ");
				switchPlayer();
			}
		}
		break;

	case O: // AI player - just do nothing
		break;
	}
}

int Game::CheckWin(int x, int y) // 0 -> Not won, 1 -> PlayerX, 2 -> PlayerO
{
	lastMove.x = x;
	lastMove.y = y;

	int horizontalPoints = 0;
	int verticalPoints = 0;

	int diagnalPoints = 0;
	int diagnalReversePoints = 0;

	int diagnalAxisStartX = x;
	int diagnalAxisStartY = y;
	while (diagnalAxisStartX > 0 && diagnalAxisStartY > 0)
	{
		diagnalAxisStartX--;
		diagnalAxisStartY--;
	}

	switch (currentPlayer)
	{
	case X:
		for (int i = 0; i < _size; i++)
		{
			if (_board[i][y] == 0 || _board[i][y] == 2)
			{
				horizontalPoints = 0;
			}
			if (_board[i][y] == 1)
			{
				horizontalPoints++;
			}
			if (horizontalPoints == _winningRowLength)
			{
				whoWon = 1;
				return 1;
			}
		}
		for (int i = 0; i < _size; i++)
		{
			if (_board[x][i] == 0 || _board[x][i] == 2)
			{
				verticalPoints = 0;
			}
			if (_board[x][i] == 1)
			{
				verticalPoints++;
			}
			if (verticalPoints >= _winningRowLength)
			{
				whoWon = 1;
				return 1;
			}
		}
		for (int i = diagnalAxisStartX, j = diagnalAxisStartY; i < _size && j < _size; i++, j++)
		{
			if (_board[i][j] == 0 || _board[i][j] == 2)
			{
				diagnalPoints = 0;
			}
			if (_board[i][j] == 1)
			{
				diagnalPoints++;
			}
			if (diagnalPoints >= _winningRowLength)
			{
				whoWon = 1;
				return 1;
			}
		}
		diagnalAxisStartX = x;
		diagnalAxisStartY = y;
		while (diagnalAxisStartX < _size - 1 && diagnalAxisStartY > 0)
		{
			diagnalAxisStartX++;
			diagnalAxisStartY--;
		}
		for (int i = diagnalAxisStartX, j = diagnalAxisStartY; i > 0 && j < _size; i--, j++)
		{
			if (_board[i][j] == 0 || _board[i][j] == 2)
			{
				diagnalReversePoints = 0;
			}
			if (_board[i][j] == 1)
			{
				diagnalReversePoints++;
			}
			if (diagnalReversePoints >= _winningRowLength)
			{
				whoWon = 1;
				return 1;
			}
		}
		break;
	case O:
		for (int i = 0; i < _size; i++)
		{
			if (_board[i][y] == 0 || _board[i][y] == 1)
			{
				horizontalPoints = 0;
			}
			if (_board[i][y] == 2)
			{
				horizontalPoints++;
			}
			if (horizontalPoints == _winningRowLength)
			{
				whoWon = 2;
				return 2;
			}
		}
		for (int i = 0; i < _size; i++)
		{
			if (_board[x][i] == 0 || _board[x][i] == 1)
			{
				verticalPoints = 0;
			}
			if (_board[x][i] == 2)
			{
				verticalPoints++;
			}
			if (verticalPoints >= _winningRowLength)
			{
				whoWon = 2;
				return 2;
			}
		}
		for (int i = diagnalAxisStartX, j = diagnalAxisStartY; i < _size && j < _size; i++, j++)
		{
			if (_board[i][j] == 0 || _board[i][j] == 1)
			{
				diagnalPoints = 0;
			}
			if (_board[i][j] == 2)
			{
				diagnalPoints++;
			}
			if (diagnalPoints >= _winningRowLength)
			{
				whoWon = 2;
				return 2;
			}
		}
		diagnalAxisStartX = x;
		diagnalAxisStartY = y;
		while (diagnalAxisStartX < _size - 1 && diagnalAxisStartY > 0)
		{
			diagnalAxisStartX++;
			diagnalAxisStartY--;
		}
		for (int i = diagnalAxisStartX, j = diagnalAxisStartY; i > 0 && j < _size; i--, j++)
		{
			if (_board[i][j] == 0 || _board[i][j] == 1)
			{
				diagnalPoints = 0;
			}
			if (_board[i][j] == 2)
			{
				diagnalPoints++;
			}
			if (diagnalPoints >= _winningRowLength)
			{
				whoWon = 2;
				return 2;
			}
		}
		break;
	}

	bool allPlacesOccupied = true;
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_board[i][j] == 0)
			{
				allPlacesOccupied = false;
			}
		}
	}
	if (allPlacesOccupied)
	{
		return -1;
	}

	return 0;
}

void Game::PlaceO(int x, int y)
{
	switch (currentPlayer)
	{
	case O: // AI player
		if (_board[x][y] == 0)
		{
			if (whoWon != 0)
			{
				return;
			}
			_board[x][y] = 2;

			sf::CircleShape circle(20 + x * oneSquareHeight, 20 + y * oneSquareHeight);
			circle.setRadius(oneSquareHeight / 2 - 4);
			circle.setFillColor(sf::Color::Transparent);
			circle.setOutlineColor(sf::Color::Blue);
			circle.setOutlineThickness(2.0);

			cirkleShapes.push_back(circle);
			if (CheckWin(boardCoordinatesX, boardCoordinatesY) == 2)
			{
				text.setFillColor(sf::Color::Red);
				text.setString("Player O won! \n Press \'R\' to restart, \n or escape to go back!");
				return;
			}
			else if (CheckWin(boardCoordinatesX, boardCoordinatesY) == -1)
			{
				text.setFillColor(sf::Color::Yellow);
				text.setString("Draw! \n Press \'R\' to restart, \n or escape to go back!");
				return;
			}

			text.setString("Current player: X ");
			switchPlayer();
		}
		break;

	case X: // Human player -> it should never happen
		break;
	}
}
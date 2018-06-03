#include "stdafx.h"
#include "GameLogic.h"


GameLogic::~GameLogic()
{
	// Deleting old board array
	for (int i = 0; i < _size; i++) {
		delete[] _arr[i];
	}
	delete[] _arr;
}

void GameLogic::init(int size, int winningRow, int **board, Player player)
{
	// Deleting old board array
	for (int i = 0; i < _size; i++) 
	{
		delete[] _arr[i];
	}
	delete[] _arr;

	_size = size;
	_winningRowLength = winningRow;
	currentPlayer = player;

	// Recreation of board array
	_arr = new int*[size];
	for (int i = 0; i < size; i++)
	{
		_arr[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			_arr[i][j] = board[i][j];
		}
	}
}

void GameLogic::setMarkX(int x, int y) 
{
	if (x < _size && x >= 0 && y < _size && y >= 0) 
	{
		_arr[x][y] = 1;
	}
}

void GameLogic::setMarkO(int x, int y) 
{
	if (x < _size && x >= 0 && y < _size && y >= 0) 
	{
		_arr[x][y] = 2;
	}
}

void GameLogic::clearMark(int x, int y) 
{
	_arr[x][y] = 0;
}

int GameLogic::checkSquare(int x, int y) 
{
	return _arr[x][y];
}

int GameLogic::CheckWin(int x, int y) // 0 -> Not won, 1 -> PlayerX, 2 -> PlayerO
{
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
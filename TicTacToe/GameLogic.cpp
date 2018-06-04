#include "stdafx.h"
#include "GameLogic.h"
#include <iostream>

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
	Display();
}

void GameLogic::Display()
{
	for (int j = 0; j < _size; j++)
	{
		for (int i = 0; i < _size; i++)
		{
			std::cout << "|" << _arr[i][j];
		}
		std::cout << "|" << std::endl;
	}
	std::cout << std::endl;
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

int GameLogic::CheckWin() {
	const int X_MARK = 1;
	const int O_MARK = 2;
	const int NO_MARK = 0;

	int playerPointsX = 0;
	int playerPointsO = 0;

	int horizontalPointsX = 0;
	int horizontalPointsO = 0;

	int verticalPointsX = 0;
	int verticalPointsO = 0;

	int diagonalRightPointsX = 0;
	int diagonalRightPointsO = 0;

	int diagonalLeftPointsX = 0;
	int diagonalLeftPointsO = 0;

	int x = 0;

	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			if (_arr[x][y] == X_MARK) {
				horizontalPointsX++;
				if (horizontalPointsO != 0) horizontalPointsO--;
			}
			else if (_arr[x][y] == O_MARK) {
				horizontalPointsO++;
				if (horizontalPointsX != 0) horizontalPointsX--;
			}
			else if (_arr[x][y] == NO_MARK) {
				if (horizontalPointsO != 0) horizontalPointsO--;
				if (horizontalPointsX != 0) horizontalPointsX--;
			}
			if (horizontalPointsX == _winningRowLength && horizontalPointsO <= _size - _winningRowLength) return X_MARK;
			else if (horizontalPointsO == _winningRowLength && horizontalPointsX <= _size - _winningRowLength) return O_MARK;

			if (_arr[y][x] == X_MARK) {
				verticalPointsX++;
				if (verticalPointsO != 0) verticalPointsO--;
			}
			else if (_arr[y][x] == O_MARK) {
				verticalPointsO++;
				if (verticalPointsX != 0) verticalPointsX--;
			}
			else if (_arr[y][x] == NO_MARK) {
				if (verticalPointsO != 0) verticalPointsO--;
				if (verticalPointsX != 0) verticalPointsX--;
			}
			if (verticalPointsX == _winningRowLength && verticalPointsO <= _size - _winningRowLength) return X_MARK;
			else if (verticalPointsO == _winningRowLength && verticalPointsX <= _size - _winningRowLength) return O_MARK;

		}
		horizontalPointsX = 0;
		horizontalPointsO = 0;
		verticalPointsX = 0;
		verticalPointsO = 0;
	}

	for (int x = 0; x <= _size - _winningRowLength; x++) {
		for (int i = 0; i < _size - x; i++) {
			if (_arr[i + x][i] == X_MARK) {
				diagonalRightPointsX++;
				if (diagonalRightPointsO != 0) diagonalRightPointsO--;
			}
			else if (_arr[i + x][i] == O_MARK) {
				diagonalRightPointsO++;
				if (diagonalRightPointsX != 0) diagonalRightPointsX--;
			}
			else if (_arr[i + x][i] == NO_MARK) {
				if (diagonalRightPointsO != 0) diagonalRightPointsO--;
				if (diagonalRightPointsX != 0) diagonalRightPointsX--;
			}
			if (diagonalRightPointsX == _winningRowLength && diagonalRightPointsO <= _size - _winningRowLength) return X_MARK;
			else if (diagonalRightPointsO == _winningRowLength && diagonalRightPointsX <= _size - _winningRowLength) return O_MARK;

			if (_arr[_size - 1 - i - x][i] == X_MARK) {
				diagonalLeftPointsX++;
				if (diagonalLeftPointsO != 0) diagonalLeftPointsO--;
			}
			else if (_arr[_size - 1 - i - x][i] == O_MARK) {
				diagonalLeftPointsO++;
				if (diagonalLeftPointsX != 0) diagonalLeftPointsX--;
			}
			else if (_arr[_size - 1 - i - x][i] == NO_MARK) {
				if (diagonalLeftPointsO != 0) diagonalLeftPointsO--;
				if (diagonalLeftPointsX != 0) diagonalLeftPointsX--;
			}
			if (diagonalLeftPointsX == _winningRowLength && diagonalLeftPointsO <= _size - _winningRowLength) return X_MARK;
			else if (diagonalLeftPointsO == _winningRowLength && diagonalLeftPointsX <= _size - _winningRowLength) return O_MARK;
		}
		diagonalRightPointsX = 0;
		diagonalRightPointsO = 0;
		diagonalLeftPointsX = 0;
		diagonalLeftPointsO = 0;
	}

	for (int x = 0; x < _size; x++) {
		for (int y = 0; y < _size; y++) {
			if (_arr[x][y] == 0) return 0;
		}
	}

	return -1;
}
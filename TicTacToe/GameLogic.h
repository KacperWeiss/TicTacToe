#pragma once
#include "Game.h"

class GameLogic
{
public:
	GameLogic();
	~GameLogic();

	void init(int size, int winningRow, int **_board, Player player);

	void setMarkX(int x, int y);
	void setMarkO(int x, int y);
	void clearMark(int x, int y);

	int checkSquare(int x, int y);

	int CheckWin() const
	{
		return whoWon;
	}

	int CheckWin(int x, int y); // -1 -> Draw, 0 -> Not won, 1 -> PlayerX, 2 -> PlayerO

	int checkSize()
	{
		return _size;
	}

private:
	int whoWon;
	int _size;
	int _winningRowLength;
	int **_arr;
	Player currentPlayer;
};


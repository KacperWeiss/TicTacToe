#pragma once
#include "Game.h"

class GameLogic
{
public:
	GameLogic() = default;
	~GameLogic();

	void init(int size, int winningRow, int **_board, Player player);

	void setMarkX(int x, int y);
	void setMarkO(int x, int y);
	void clearMark(int x, int y);

	int checkSquare(int x, int y);

	int CheckWin();

	int checkSize()
	{
		return _size;
	}

	void Display();

private:
	int _size;
	int _winningRowLength;
	int **_arr;
	Player currentPlayer;
};


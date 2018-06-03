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

	int CheckWin(int x, int y); // -1 -> Draw, 0 -> Not won, 1 -> PlayerX, 2 -> PlayerO

private:
	int _size;
	int _winningRowLength;
	int **_arr;
	Player currentPlayer;
};


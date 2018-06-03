#pragma once
#include "GameLogic.h"

struct Move 
{
	Move() {};
	Move(int Score) : score(Score) {};

	int x;
	int y;
	int score;
};

class PlayerAI
{
public:
	PlayerAI() = default;
	~PlayerAI() = default;

	Move placeMark(Game *game, GameLogic *gameLogic, int x, int y);
	Move miniMax(GameLogic *gameLogic, int depth, int player, int x, int y);
	Move alphaBeta(GameLogic *gameLogic, int depth, int alpha, int beta, int Player, int x, int y);
};


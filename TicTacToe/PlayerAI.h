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

	Move placeMark(Game *game, GameLogic *gameLogic, int difficulty);
	Move miniMax(GameLogic *gameLogic, int depth, int player);
	Move alphaBeta(GameLogic *gameLogic, int depth, int alpha, int beta, int Player);
};


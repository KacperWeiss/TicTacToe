#include "stdafx.h"
#include "PlayerAI.h"
#include <vector>
#include <algorithm>
#include <iostream>

int const AI_PLAYER = 2;
int const HUMAN_PLAYER = 1;
int const NO_MARK = 0;
int const TIE = -1;

int const MAX_PLAYER = 2;
int const MIN_PLAYER = 1;

Move PlayerAI::placeMark(Game *game, GameLogic *gameLogic, int difficulty) {

	Move bestMove;
	bestMove = alphaBeta(gameLogic, difficulty, -1000000, 1000000, MAX_PLAYER);
	gameLogic->setMarkO(bestMove.x, bestMove.y);
	gameLogic->Display();
	game->PlaceO(bestMove.x, bestMove.y);

	return bestMove;
}

Move PlayerAI::miniMax(GameLogic *gameLogic, int depth, int player) {

	int result = gameLogic->CheckWin();

	if (result == AI_PLAYER) {
		return Move(10);
	}
	else if (result == HUMAN_PLAYER) {
		return Move(-10);
	}
	else if (result == TIE) {
		return Move(0);
	}
	else if (depth == 1) {
		return Move(0);
	}

	std::vector<Move> moves;

	for (int x = 0; x < gameLogic->checkSize(); x++) {
		for (int y = 0; y < gameLogic->checkSize(); y++) {
			if (gameLogic->checkSquare(x, y) == NO_MARK) {
				Move move;
				move.x = x;
				move.y = y;

				// tura AI
				if (player == AI_PLAYER) {
					gameLogic->setMarkO(x, y);
					move.score = miniMax(gameLogic, depth - 1, HUMAN_PLAYER).score;
				}
				// tura gracza
				else if (player == HUMAN_PLAYER) {
					gameLogic->setMarkX(x, y);
					move.score = miniMax(gameLogic, depth - 1, AI_PLAYER).score;
				}

				moves.push_back(move);

				gameLogic->clearMark(x, y);
			}
		}
	}

	int bestMove = 0;
	if (player == AI_PLAYER) {
		int bestScore = -100000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score > bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}
	else {
		int bestScore = 100000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score < bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}

	return moves[bestMove];
}

Move PlayerAI::alphaBeta(GameLogic *gameLogic, int depth, int alpha, int beta, int player) 
{
	int v;
	int result = gameLogic->CheckWin();

	if (result == MAX_PLAYER) {
		return Move(10);
	}
	else if (result == MIN_PLAYER) {
		return Move(-10);
	}
	else if (result == TIE) {
		return Move(0);
	}
	else if (depth == 1) {
		return Move(0);
	}


	std::vector<Move> moves;

	if (player == MAX_PLAYER) v = -100000;
	else if (player == MIN_PLAYER) v = 100000;

	for (int x = 0; x < gameLogic->checkSize(); x++) {
		for (int y = 0; y < gameLogic->checkSize(); y++) {
			if (gameLogic->checkSquare(x, y) == NO_MARK) {
				Move move;
				move.x = x;
				move.y = y;

				// tura AI
				if (player == MAX_PLAYER) {
					gameLogic->setMarkO(x, y);
					move.score = alphaBeta(gameLogic, depth - 1, alpha, beta, MIN_PLAYER).score;
					v = std::max(v, move.score);
					alpha = std::max(alpha, v);
				}
				// tura gracza
				else if (player == MIN_PLAYER) {
					gameLogic->setMarkX(x, y);
					move.score = alphaBeta(gameLogic, depth - 1, alpha, beta, MAX_PLAYER).score;
					v = std::min(v, move.score);
					beta = std::min(beta, v);
				}

				moves.push_back(move);

				gameLogic->clearMark(x, y);
				if (beta <= alpha) break;
			}
		}
	}

	int bestMove = 0;
	int movesSize = moves.size();

	if (player == MAX_PLAYER) {
		int bestScore = -100000;
		for (int i = 0; i < movesSize; i++) {
			if (moves[i].score > bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}
	else {
		int bestScore = 100000;
		for (int i = 0; i < movesSize; i++) {
			if (moves[i].score < bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}

	return moves[bestMove];
}

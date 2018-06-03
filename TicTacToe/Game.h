#pragma once
#include <SFML\/Graphics.hpp>
#include "CrossShape.h"

#define MAX_NUMBER_OF_SIDES 4

enum Player
{
	X, O
};

class Game
{
public:
	Game(float width, float height, int size, int winningRow);
	Game() = delete;
	~Game();

	void Reconfigure(float width, float height, int size, int winningRow);
	void Draw(sf::RenderWindow &window);
	void DetectMouseClick(int x, int y);	

	int CheckWin() const
	{
		return whoWon;
	}
	int **GetBoard() const
	{
		return _board;
	}

	int CheckWin(int x, int y); // -1 -> Draw, 0 -> Not won, 1 -> PlayerX, 2 -> PlayerO

	Player GetCurrentPlayer() const
	{
		return currentPlayer;
	}

	void switchPlayer();

	sf::Vector2i GetLastMove()
	{
		return lastMove;
	}

	void PlaceO(int x, int y);

private:
	sf::RectangleShape boardOutline;
	sf::RectangleShape *boardInsideLines;
	std::vector<sf::CircleShape> cirkleShapes;
	std::vector<CrossShape> crossShapes;
	sf::Text text;
	sf::Font font;
	int _size;
	int _winningRowLength;
	int **_board;	// 0 -> Empty, 1 -> PlayerX, 2 -> PlayerO

	Player currentPlayer;
	float oneSquareHeight;
	int boardCoordinatesX;
	int boardCoordinatesY;
	int whoWon;

	sf::Vector2i lastMove;
};


#pragma once
#include <SFML\/Graphics.hpp>

#define MAX_NUMBER_OF_SIDES 4

class Game
{
public:
	Game(float width, float height, int size, int winningRow);
	Game() = delete;
	~Game();

	void Draw(sf::RenderWindow &window);
	void Reconfigure(float width, float height, int size, int winningRow);

private:
	sf::RectangleShape boardOutline[MAX_NUMBER_OF_SIDES];
	sf::RectangleShape *boardInsideLines;
	int _size;
	int _winningRowLength;
	int **_board;
};


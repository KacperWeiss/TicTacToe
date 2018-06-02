#pragma once
#include <SFML\/Graphics.hpp>

#define MAX_NUMBER_OF_MENU_ITEMS 3

enum OptionsState
{
	Navigation, ChangingValues
};

class Options
{
public:
	Options(float width, float height);
	~Options() = default;

	void Draw(sf::RenderWindow &window);
	void ChangeState();
	void MoveUp();
	void MoveDown();

	int GetSelectedItem() { return selectedItemIndex; }
	int GetBoardSize() { return boardSizeValue; }
	int GetWinningRow() { return winningRowsValue; }
	OptionsState GetCurrentOptionsState() { return currentState; }

private:
	OptionsState currentState;
	int selectedItemIndex;
	int boardSizeValue;
	int winningRowsValue;
	sf::Font font;
	sf::Text menuItem[MAX_NUMBER_OF_MENU_ITEMS];
	sf::Text valueItem[MAX_NUMBER_OF_MENU_ITEMS - 1];
};


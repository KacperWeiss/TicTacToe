#pragma once
#include <SFML\/Graphics.hpp>

#define MAX_NUMBER_OF_MENU_ITEMS 4

enum OptionsState
{
	Navigation, ChangingValues
};

enum Difficulties
{
	Easy, Medium, Hard, Impossible
};

class Options
{
public:
	Options(float width, float height);
	Options() = delete;
	~Options() = default;

	void Draw(sf::RenderWindow &window);
	void ChangeState();
	void MoveUp();
	void MoveDown();

	int GetSelectedItem() { return selectedItemIndex; }
	int GetBoardSize() { return boardSizeValue; }
	int GetWinningRow() { return winningRowsValue; }
	OptionsState GetCurrentOptionsState() { return currentState; }

	int GetDifficulty();

private:
	OptionsState currentState;
	int selectedItemIndex;
	int boardSizeValue;
	int winningRowsValue;
	sf::Font font;
	sf::Text menuItem[MAX_NUMBER_OF_MENU_ITEMS];
	sf::Text valueItem[MAX_NUMBER_OF_MENU_ITEMS - 1];

	Difficulties difficulty;

	std::string GetDifficultyString();
};


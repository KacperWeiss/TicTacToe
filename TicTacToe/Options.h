#pragma once
#include <SFML\/Graphics.hpp>

#define MAX_NUMBER_OF_MENU_ITEMS 3

class Options
{
public:
	Options(float width, float height);
	~Options() = default;

	void Draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	int boardSizeValue;
	int winningRowsValue;
	sf::Font font;
	sf::Text menuItem[MAX_NUMBER_OF_MENU_ITEMS];
	sf::Text valueItem[MAX_NUMBER_OF_MENU_ITEMS - 1];
};


#pragma once
#include <SFML\/Graphics.hpp>

#define MAX_NUMBER_OF_MENU_ITEMS 3

class Menu
{
public:
	Menu(float width, float height);
	~Menu() = default;

	void Draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menuItem[MAX_NUMBER_OF_MENU_ITEMS];
};
#include "stdafx.h"
#include "Options.h"


Options::Options(float width, float height)
{
	if (!font.loadFromFile("ComicSansMS3.ttf"))
	{
		// error handling (will be done in future)
	}

	selectedItemIndex = 0;
	boardSizeValue = 3;
	winningRowsValue = 3;
	
	menuItem[0].setFont(font);
	menuItem[0].setFillColor(sf::Color::White);
	menuItem[0].setOutlineThickness(1.0);
	menuItem[0].setOutlineColor(sf::Color::Green);
	menuItem[0].setString("Set size: ");
	menuItem[0].setPosition(sf::Vector2f(width / 3, height / (MAX_NUMBER_OF_MENU_ITEMS + 1) * 1));

	valueItem[0].setFont(font);
	valueItem[0].setFillColor(sf::Color::White);
	valueItem[0].setOutlineThickness(1.0);
	valueItem[0].setOutlineColor(sf::Color::White);
	valueItem[0].setString(std::to_string(boardSizeValue));
	valueItem[0].setPosition(sf::Vector2f((2 * width) / 3, height / (MAX_NUMBER_OF_MENU_ITEMS + 1) * 1));

	menuItem[1].setFont(font);
	menuItem[1].setFillColor(sf::Color::White);
	menuItem[1].setOutlineThickness(1.0);
	menuItem[1].setOutlineColor(sf::Color::White);
	menuItem[1].setString("Set winning rows: ");
	menuItem[1].setPosition(sf::Vector2f(width / 3, height / (MAX_NUMBER_OF_MENU_ITEMS + 1) * 2));

	valueItem[1].setFont(font);
	valueItem[1].setFillColor(sf::Color::White);
	valueItem[1].setOutlineThickness(1.0);
	valueItem[1].setOutlineColor(sf::Color::White);
	valueItem[1].setString(std::to_string(winningRowsValue));
	valueItem[1].setPosition(sf::Vector2f((2 * width) / 3, height / (MAX_NUMBER_OF_MENU_ITEMS + 1) * 2));

	menuItem[2].setFont(font);
	menuItem[2].setFillColor(sf::Color::White);
	menuItem[2].setOutlineThickness(1.0);
	menuItem[2].setOutlineColor(sf::Color::White);
	menuItem[2].setString("Back");
	menuItem[2].setPosition(sf::Vector2f(width / 3, height / (MAX_NUMBER_OF_MENU_ITEMS + 1) * 3));

}

void Options::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_MENU_ITEMS; i++)
	{
		window.draw(menuItem[i]);
	}
	for (int i = 0; i < MAX_NUMBER_OF_MENU_ITEMS - 1; i++)
	{
		window.draw(valueItem[i]);
	}
}

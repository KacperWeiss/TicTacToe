#include "stdafx.h"
#include "Menu.h"


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("ComicSansMS3.ttf"))
	{
		// error handling (will be done in future)
	}

	menuItem[0].setFont(font);
	menuItem[0].setFillColor(sf::Color::White);
	menuItem[0].setOutlineThickness(1.0);
	menuItem[0].setOutlineColor(sf::Color::Green);
	menuItem[0].setString("Play");
	menuItem[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_MENU_ITEMS + 1) * 1));
	
	menuItem[1].setFont(font);
	menuItem[1].setFillColor(sf::Color::White);
	menuItem[1].setOutlineThickness(1.0);
	menuItem[1].setOutlineColor(sf::Color::White);
	menuItem[1].setString("Options");
	menuItem[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_MENU_ITEMS + 1) * 2));
	
	menuItem[2].setFont(font);
	menuItem[2].setFillColor(sf::Color::White);
	menuItem[2].setOutlineThickness(1.0);
	menuItem[2].setOutlineColor(sf::Color::White);
	menuItem[2].setString("Exit");
	menuItem[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_MENU_ITEMS + 1) * 3));

	selectedItemIndex = 0;
}

void Menu::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_MENU_ITEMS; i++)
	{
		window.draw(menuItem[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0) 
	{
		menuItem[selectedItemIndex].setOutlineColor(sf::Color::White);
		selectedItemIndex--;
		menuItem[selectedItemIndex].setOutlineColor(sf::Color::Green);
	}
}

void Menu::MoveDown() 
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_MENU_ITEMS)
	{
		menuItem[selectedItemIndex].setOutlineColor(sf::Color::White);
		selectedItemIndex++;
		menuItem[selectedItemIndex].setOutlineColor(sf::Color::Green);
	}
}
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
	currentState = OptionsState::Navigation;
	
	menuItem[0].setFont(font);
	menuItem[0].setFillColor(sf::Color::White);
	menuItem[0].setOutlineThickness(1.0);
	menuItem[0].setOutlineColor(sf::Color::Green);
	menuItem[0].setString("Set size: ");
	menuItem[0].setPosition(sf::Vector2f(width / 3, height / (MAX_NUMBER_OF_MENU_ITEMS + 1) * 1));

	valueItem[0].setFont(font);
	valueItem[0].setFillColor(sf::Color::White);
	valueItem[0].setOutlineThickness(1.0);
	valueItem[0].setOutlineColor(sf::Color::Green);
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

void Options::ChangeState()
{
	if (currentState == OptionsState::Navigation && selectedItemIndex != 2)
	{
		currentState = OptionsState::ChangingValues;

		menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
		valueItem[selectedItemIndex].setFillColor(sf::Color::Red);

		menuItem[selectedItemIndex].setOutlineColor(sf::Color::Red);
		valueItem[selectedItemIndex].setOutlineColor(sf::Color::Red);
	}
	else if (currentState == OptionsState::ChangingValues)
	{
		currentState = OptionsState::Navigation;

		menuItem[selectedItemIndex].setFillColor(sf::Color::White);
		valueItem[selectedItemIndex].setFillColor(sf::Color::White);

		menuItem[selectedItemIndex].setOutlineColor(sf::Color::Green);
		valueItem[selectedItemIndex].setOutlineColor(sf::Color::Green);
	}
}

void Options::MoveUp()
{
	switch (currentState)
	{
	case Navigation:
		if (selectedItemIndex - 1 >= 0)
		{
			menuItem[selectedItemIndex].setOutlineColor(sf::Color::White);
			valueItem[selectedItemIndex].setOutlineColor(sf::Color::White);
			selectedItemIndex--;
			menuItem[selectedItemIndex].setOutlineColor(sf::Color::Green);
			valueItem[selectedItemIndex].setOutlineColor(sf::Color::Green);
		}
		break;
	case ChangingValues:
		switch (selectedItemIndex)
		{
		case 0: // Size
			if (boardSizeValue < 10)
			{
				boardSizeValue++;
				valueItem[0].setString(std::to_string(boardSizeValue));
			}
			break;
		case 1: // Winning rows
			if (winningRowsValue < 10 && winningRowsValue < boardSizeValue)
			{
				winningRowsValue++;
				valueItem[1].setString(std::to_string(winningRowsValue));
			}
			break;
		default:
			break;
		}

		break;
	default:
		break;
	}
}

void Options::MoveDown()
{
	switch (currentState)
	{
	case Navigation:
		if (selectedItemIndex + 1 < MAX_NUMBER_OF_MENU_ITEMS)
		{
			menuItem[selectedItemIndex].setOutlineColor(sf::Color::White);
			valueItem[selectedItemIndex].setOutlineColor(sf::Color::White);
			selectedItemIndex++;
			menuItem[selectedItemIndex].setOutlineColor(sf::Color::Green);
			valueItem[selectedItemIndex].setOutlineColor(sf::Color::Green);
		}
		break;
	case ChangingValues:
		switch (selectedItemIndex)
		{
		case 0: // Size
			if (boardSizeValue - 1 >= 3 && winningRowsValue < boardSizeValue)
			{
				boardSizeValue--;
				valueItem[0].setString(std::to_string(boardSizeValue));
			}
			break;
		case 1: // Winning rows
			if (winningRowsValue - 1 >= 3)
			{
				winningRowsValue--;
				valueItem[1].setString(std::to_string(winningRowsValue));
			}
			break;
		default:
			break;
		}

		break;
	default:
		break;
	}
}

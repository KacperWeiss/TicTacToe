#include "stdafx.h"
#include "CrossShape.h"


CrossShape::CrossShape(float x, float y, float size)
{
	rectangleShapes[0].setPosition(x, y);
	rectangleShapes[0].setSize(sf::Vector2f(size * sqrt(2), 2.0));
	rectangleShapes[0].setFillColor(sf::Color::Magenta);
	rectangleShapes[0].setRotation(45);

	rectangleShapes[1].setPosition(x + size, y);
	rectangleShapes[1].setSize(sf::Vector2f(size * sqrt(2), 2.0));
	rectangleShapes[1].setFillColor(sf::Color::Magenta);
	rectangleShapes[1].setRotation(135);
}

void CrossShape::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
	target.draw(this->rectangleShapes[0], state);
	target.draw(this->rectangleShapes[1], state);
}

void CrossShape::SetFillColor(sf::Color color)
{
	rectangleShapes[0].setFillColor(color);
	rectangleShapes[1].setFillColor(color);
}
#pragma once
#include <SFML/Graphics.hpp>

class CrossShape : public sf::Drawable
{
public:
	CrossShape(float x, float y, float size);
	CrossShape() = delete;
	~CrossShape() = default;

	void SetFillColor(sf::Color color);
	void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

private:
	sf::RectangleShape rectangleShapes[2];
};


#pragma once
#include <SFML\Graphics.hpp>
#include <Window.h>

class Tile{
public:
	Tile(float x, float y, float width, float height, sf::Color color);
	bool isOpen();
	void setOpen(bool open);
	void Draw(SFGE::Window& window);


private:
	sf::Vector2f m_position;
	bool m_isOpen;
	sf::Color m_color;
	sf::RectangleShape m_shape;
};
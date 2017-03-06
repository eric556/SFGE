#pragma once
#include <SFML\Graphics.hpp>
#include "Map.h"



class Entity{
public:
	enum Direction { UP, DOWN, LEFT, RIGHT, NONE};
	Entity(int x, int y, float width, float height, Map& map);
	void Draw(SFGE::Window& window);
	void move(int x, int y);
	void update(float dt);
private:
	sf::Vector2f position;
	sf::Vector2f size;
	Map& m_map;
	Direction m_moveDirection;
	sf::RectangleShape m_shape;
};
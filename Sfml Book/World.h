#pragma once
#include "Snake.h"
#include "Pickup.h"
#include <fstream>
#include <vector>
class World
{
public:
	World(sf::Vector2u l_windSize);
	~World();

	int GetBlockSize();

	void Update(Snake& l_player);
	void Render(sf::RenderWindow& l_window);

private:
	sf::Vector2u m_windowSize;
	int m_blockSize;
	Pickup m_pickup;
	std::vector<Pickup> m_pickups;
	sf::RectangleShape m_bounds[4];
};


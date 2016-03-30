#include "World.h"


World::World(sf::Vector2u l_windSize) : m_pickup(PickupType::Extend, sf::Vector2i(4, 4), 8)
{
	m_blockSize = 16;
	m_windowSize = l_windSize;
	m_pickups.push_back(m_pickup);

	for (int i = 0; i < 4; ++i){
		m_bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2)){
			m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
		}
		else {
			m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
		}
		if (i < 2){
			m_bounds[i].setPosition(0, 0);
		}
		else {
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
		}
	}
}


World::~World()
{
}


void World::Update(Snake& l_player){
	srand(time(NULL));

	if (l_player.GetScore() == 100 && m_pickups.size() < 2){
		Pickup p(PickupType::Extend, sf::Vector2i(rand() % 4+1,rand() % 4 + 1), 8);
		m_pickups.push_back(p);
	}
	else if (l_player.GetScore() == 200 && m_pickups.size() < 3){
		Pickup p(PickupType::Extend, sf::Vector2i(rand() % 4 + 1, rand() % 4 + 1), 8);
		m_pickups.push_back(p);
	}
	else if (l_player.GetScore() == 300 && m_pickups.size() < 4){
		Pickup p(PickupType::Extend, sf::Vector2i(rand() % 4 + 1, rand() % 4 + 1), 8);
		m_pickups.push_back(p);
	}


	for (int i = 0; i < m_pickups.size(); i++){
		m_pickups[i].Update(l_player, m_windowSize, m_bounds);
	}
	

	int gridSize_x = m_windowSize.x / m_blockSize;
	int gridSize_y = m_windowSize.y / m_blockSize;

	if (l_player.GetPosition().x <= 0 || l_player.GetPosition().y <= 0 || l_player.GetPosition().x >= gridSize_x - 1 || l_player.GetPosition().y >= gridSize_y - 1){
		l_player.Lose();
	}
}

void World::Render(sf::RenderWindow& l_window){
	for (int i = 0; i < 4; i++){
		l_window.draw(m_bounds[i]);
	}
	for (int i = 0; i < m_pickups.size(); i++){
		m_pickups[i].Render(l_window);
	}
}



int World::GetBlockSize(){ return m_blockSize; }


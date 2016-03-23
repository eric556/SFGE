#pragma once
#include "Snake.h"
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
class GUI
{
public:
	GUI(Snake& l_player, sf::Vector2u l_windSize);
	~GUI();

	void Update(Snake& l_player);
	void Render(sf::RenderWindow& l_window);
private:
	int m_playerLives;
	int m_playerScore;
	std::vector<sf::Text> m_playerInfo;
	sf::Font m_font;
	Snake m_player;
	sf::Color m_textColor;

};


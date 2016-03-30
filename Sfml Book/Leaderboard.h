#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
class Leaderboard
{
public:
	Leaderboard(sf::Vector2u l_windSize);
	~Leaderboard();

	void Update();
	void Render(sf::RenderWindow& l_window);

private:

	sf::Font m_font;
	sf::Text m_title;
	sf::Color m_textColor;
	std::vector<sf::Text> m_leaderBoards;

};


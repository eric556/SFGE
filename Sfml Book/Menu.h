#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
class Menu
{
public:
	Menu(sf::Vector2u l_windSize);
	~Menu();

	void Update();
	void Render(sf::RenderWindow& l_window);
private:
	sf::Font m_font;
	sf::Text m_title;
	std::vector<sf::Text> m_menuOptions;
	sf::Color m_textColor;


};


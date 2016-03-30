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
	void HandleInput();
	int menuIndex;
	std::vector<sf::Text> menuOptions;
private:
	sf::Font m_font;
	sf::Text m_title;
	sf::Color m_textColor;


};


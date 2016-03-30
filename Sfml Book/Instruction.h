#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
class Instruction
{
public:
	Instruction(sf::Vector2u l_windSize);
	~Instruction();

	void Update();
	void Render(sf::RenderWindow& l_windows);

private:
	sf::Font m_font;
	sf::Text m_title;
	sf::Color m_textColor;
	std::vector<sf::Text> m_text;
	std::vector<sf::Text> m_dotText;
	std::vector<sf::CircleShape> m_dots;

};


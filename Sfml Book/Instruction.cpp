#include "Instruction.h"


Instruction::Instruction(sf::Vector2u l_windSize)
{
	if (!m_font.loadFromFile("CubicCoreMono.ttf")){

	}
	m_textColor = sf::Color(23, 87, 100);
	m_title.setFont(m_font);
	m_title.setCharacterSize(100);
	m_title.setString("Instructions");
	m_title.setColor(m_textColor);
	sf::FloatRect titleTextRect = m_title.getLocalBounds();
	m_title.setOrigin(sf::Vector2f(titleTextRect.width / 2, titleTextRect.height / 2));
	m_title.setPosition(sf::Vector2f(l_windSize.x / 2, 0));

	m_text.push_back(sf::Text("Play using the arrow keys", m_font, 50));
	m_text.push_back(sf::Text("Backspace to go to Main Menu", m_font, 50));
	m_text.push_back(sf::Text( "Pick up the dots to get points",m_font, 50));
	m_text.push_back(sf::Text("There are diffrent kinds of dots", m_font, 50));
	
	for (int i = 0; i < m_text.size(); i++){
		m_text[i].setColor(m_textColor);
		sf::FloatRect textRect = m_text[i].getLocalBounds();
		m_text[i].setOrigin(sf::Vector2f(textRect.width / 2, textRect.height / 2));
		m_text[i].setPosition((l_windSize.x/2),(l_windSize.y/4) + (m_text[i].getCharacterSize()*i) - 60);
	}

	m_dotText.push_back(sf::Text("*Extend Snake", m_font, 40));
	m_dotText.push_back(sf::Text("*Speed Up", m_font, 40));
	m_dotText.push_back(sf::Text("*Slow Down", m_font, 40));
	m_dotText.push_back(sf::Text("*Increase Arena Size", m_font, 40));
	m_dotText.push_back(sf::Text("*Decrease Arena Size", m_font, 40));
	m_dotText.push_back(sf::Text("Extra Life", m_font, 40));

	for (int i = 0; i < m_dotText.size(); i++){
		m_dotText[i].setColor(m_textColor);
		sf::FloatRect textRect = m_dotText[i].getLocalBounds();
		m_dotText[i].setPosition(l_windSize.x/5,(l_windSize.y/2) + (m_dotText[i].getCharacterSize() * i));
	}

	for (int i = 0; i < 6; i++){
		m_dots.push_back(sf::CircleShape(12.f));
	}
	m_dots[0].setFillColor(sf::Color::Red);
	m_dots[1].setFillColor(sf::Color(158, 65, 207));
	m_dots[2].setFillColor(sf::Color(255 - 158, 255 - 65, 255 - 207));
	m_dots[3].setFillColor(sf::Color(226, 125, 8));
	m_dots[4].setFillColor(sf::Color(255 - 226, 255 - 125, 255 - 8));
	m_dots[5].setFillColor(sf::Color(231, 236, 19));

	for (int i = 0; i < m_dots.size(); i++){
		m_dots[i].setPosition(m_dotText[i].getPosition().x + 300, m_dotText[i].getPosition().y + 18);
	}

}


Instruction::~Instruction()
{
}

void Instruction::Render(sf::RenderWindow& l_window){
	l_window.draw(m_title);
	for (int i = 0; i < m_text.size(); i++){
		l_window.draw(m_text[i]);
	}
	for (int i = 0; i < m_dotText.size(); i++){
		l_window.draw(m_dotText[i]);
	}

	for (int i = 0; i < m_dots.size(); i++){
		l_window.draw(m_dots[i]);
	}
}

void Instruction::Update(){

}
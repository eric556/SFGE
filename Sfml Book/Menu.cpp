#include "Menu.h"


Menu::Menu(sf::Vector2u l_windSize)
{
	if (!m_font.loadFromFile("CubicCoreMono.ttf")){

	}
	m_textColor = sf::Color(23, 87, 100);

	m_title.setFont(m_font);
	m_title.setString("SNAKE");
	m_title.setCharacterSize(200);
	m_title.setColor(m_textColor);
	sf::FloatRect titleTextRect = m_title.getLocalBounds();
	m_title.setOrigin(titleTextRect.width / 2, titleTextRect.height / 2);
	m_title.setPosition(l_windSize.x / 2, 0);

	m_menuOptions.push_back(sf::Text("Play",m_font,50));
	m_menuOptions.push_back(sf::Text("Instructions", m_font, 50));
	m_menuOptions.push_back(sf::Text("Exit", m_font, 50));

	for (int i = 0; i < m_menuOptions.size(); i++){
		m_menuOptions[i].setColor(m_textColor);
		sf::FloatRect textRect = m_menuOptions[i].getLocalBounds();
		m_menuOptions[i].setOrigin(textRect.width/2,textRect.height/2);
		m_menuOptions[i].setPosition(sf::Vector2f(l_windSize.x / 2, (l_windSize.y / 2) + (m_menuOptions[i].getCharacterSize() * i)));
	}

}

void Menu::Render(sf::RenderWindow& l_window){
	l_window.draw(m_title);
	for (int i = 0; i < m_menuOptions.size(); i++){
		l_window.draw(m_menuOptions[i]);
	}

}


Menu::~Menu()
{
}

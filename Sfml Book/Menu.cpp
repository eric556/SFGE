#include "Menu.h"


Menu::Menu(sf::Vector2u l_windSize)
{
	if (!m_font.loadFromFile("CubicCoreMono.ttf")){

	}
	m_textColor = sf::Color(23, 87, 100);
	menuIndex = 0;

	m_title.setFont(m_font);
	m_title.setString("SNAKE");
	m_title.setCharacterSize(200);
	m_title.setColor(m_textColor);
	sf::FloatRect titleTextRect = m_title.getLocalBounds();
	m_title.setOrigin(titleTextRect.width / 2, titleTextRect.height / 2);
	m_title.setPosition(l_windSize.x / 2, 0);

	menuOptions.push_back(sf::Text("Play",m_font,50));
	menuOptions.push_back(sf::Text("Instructions", m_font, 50));
	menuOptions.push_back(sf::Text("Leader Boards", m_font, 50));
	menuOptions.push_back(sf::Text("Exit", m_font, 50));

	for (int i = 0; i < menuOptions.size(); i++){
		menuOptions[i].setColor(m_textColor);
		sf::FloatRect textRect = menuOptions[i].getLocalBounds();
		menuOptions[i].setOrigin(textRect.width/2,textRect.height/2);
		menuOptions[i].setPosition(sf::Vector2f(l_windSize.x / 2, (l_windSize.y / 2) + (menuOptions[i].getCharacterSize() * i)));
	}
	
}

void Menu::Render(sf::RenderWindow& l_window){
	l_window.draw(m_title);
	for (int i = 0; i < menuOptions.size(); i++){
		l_window.draw(menuOptions[i]);
	}

}

void Menu::Update(){
	for (int i = 0; i < menuOptions.size(); i++){
		menuOptions[i].setColor(m_textColor);
	}
	menuOptions[menuIndex].setColor(sf::Color(255 - m_textColor.r, 255 - m_textColor.g, 255 - m_textColor.b));
}

void Menu::HandleInput(){
	
	
}


Menu::~Menu()
{
}
